#include "api.h"
#include "ascon.h"
#include "crypto_aead.h"
#include "permutations.h"
#include "printstate.h"

#define AVX512_SHUFFLE_U64BIG                                  \
  _mm512_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, /* word 7 */ \
                  -1, -1, -1, -1, -1, -1, -1, -1, /* word 6 */ \
                  -1, -1, -1, -1, -1, -1, -1, -1, /* word 5 */ \
                  -1, -1, -1, -1, -1, -1, -1, -1, /* word 4 */ \
                  -1, -1, -1, -1, -1, -1, -1, -1, /* word 3 */ \
                  -1, -1, -1, -1, -1, -1, -1, -1, /* word 2 */ \
                  8, 9, 10, 11, 12, 13, 14, 15,   /* word 1 */ \
                  0, 1, 2, 3, 4, 5, 6, 7)         /* word 0 */

#if !ASCON_INLINE_MODE
#undef forceinline
#define forceinline
#endif

#ifdef ASCON_AEAD_RATE

forceinline void ascon_loadkey(ascon_key_t* key, const uint8_t* k) {
#if CRYPTO_KEYBYTES == 16
  key->x[0] = LOAD(k, 8);
  key->x[1] = LOAD(k + 8, 8);
#else /* CRYPTO_KEYBYTES == 20 */
  key->x[0] = KEYROT(0, LOADBYTES(k, 4));
  key->x[1] = LOADBYTES(k + 4, 8);
  key->x[2] = LOADBYTES(k + 12, 8);
#endif
}

forceinline void ascon_initaead(ascon_state_t* s, const ascon_key_t* key,
                                const uint8_t* npub) {
#if CRYPTO_KEYBYTES == 16
  if (ASCON_AEAD_RATE == 8) s->x[0] = ASCON_128_IV;
  if (ASCON_AEAD_RATE == 16) s->x[0] = ASCON_128A_IV;
  s->x[1] = key->x[0];
  s->x[2] = key->x[1];
#else /* CRYPTO_KEYBYTES == 20 */
  s->x[0] = key->x[0] ^ ASCON_80PQ_IV;
  s->x[1] = key->x[1];
  s->x[2] = key->x[2];
#endif
  s->x[3] = LOAD(npub, 8);
  s->x[4] = LOAD(npub + 8, 8);
  printstate("init 1st key xor", s);
  P(s, 12);
#if CRYPTO_KEYBYTES == 16
  s->x[3] ^= key->x[0];
  s->x[4] ^= key->x[1];
#else /* CRYPTO_KEYBYTES == 20 */
  s->x[2] ^= key->x[0];
  s->x[3] ^= key->x[1];
  s->x[4] ^= key->x[2];
#endif
  printstate("init 2nd key xor", s);
}

forceinline void ascon_adata(ascon_state_t* s, const uint8_t* ad,
                             uint64_t adlen) {
  const __m512i u64big = AVX512_SHUFFLE_U64BIG;
  const int mask = (ASCON_AEAD_RATE == 8) ? 0xff : 0xffff;
  const int nr = (ASCON_AEAD_RATE == 8) ? 6 : 8;
  if (adlen) {
    /* full associated data blocks */
    while (adlen >= ASCON_AEAD_RATE) {
      ascon_state_t t;
      t.z = _mm512_maskz_loadu_epi8(mask, ad);
      t.z = _mm512_maskz_shuffle_epi8(mask, t.z, u64big);
      s->z = _mm512_xor_epi64(s->z, t.z);
      printstate("absorb adata", s);
      P(s, nr);
      ad += ASCON_AEAD_RATE;
      adlen -= ASCON_AEAD_RATE;
    }
    /* final associated data block */
    uint64_t* px = &s->x[0];
    if (ASCON_AEAD_RATE == 16 && adlen >= 8) {
      s->x[0] ^= LOAD(ad, 8);
      px = &s->x[1];
      ad += 8;
      adlen -= 8;
    }
    *px ^= PAD(adlen);
    if (adlen) *px ^= LOADBYTES(ad, adlen);
    printstate("pad adata", s);
    P(s, nr);
  }
  /* domain separation */
  s->x[4] ^= DSEP();
  printstate("domain separation", s);
}

forceinline void ascon_encrypt(ascon_state_t* s, uint8_t* c, const uint8_t* m,
                               uint64_t mlen) {
  const __m512i u64big = AVX512_SHUFFLE_U64BIG;
  const int mask = (ASCON_AEAD_RATE == 8) ? 0xff : 0xffff;
  const int nr = (ASCON_AEAD_RATE == 8) ? 6 : 8;
  /* full plaintext blocks */
  while (mlen >= ASCON_AEAD_RATE) {
    ascon_state_t t;
    t.z = _mm512_maskz_loadu_epi8(mask, m);
    t.z = _mm512_maskz_shuffle_epi8(mask, t.z, u64big);
    s->z = _mm512_xor_epi64(s->z, t.z);
    t.z = _mm512_maskz_shuffle_epi8(mask, s->z, u64big);
    _mm512_mask_storeu_epi8(c, mask, t.z);
    printstate("absorb plaintext", s);
    P(s, nr);
    m += ASCON_AEAD_RATE;
    c += ASCON_AEAD_RATE;
    mlen -= ASCON_AEAD_RATE;
  }
  /* final plaintext block */
  uint64_t* px = &s->x[0];
  if (ASCON_AEAD_RATE == 16 && mlen >= 8) {
    s->x[0] ^= LOAD(m, 8);
    STORE(c, s->x[0], 8);
    px = &s->x[1];
    m += 8;
    c += 8;
    mlen -= 8;
  }
  *px ^= PAD(mlen);
  if (mlen) {
    *px ^= LOADBYTES(m, mlen);
    STOREBYTES(c, *px, mlen);
  }
  printstate("pad plaintext", s);
}

forceinline void ascon_decrypt(ascon_state_t* s, uint8_t* m, const uint8_t* c,
                               uint64_t clen) {
  const __m512i u64big = AVX512_SHUFFLE_U64BIG;
  const int mask = (ASCON_AEAD_RATE == 8) ? 0xff : 0xffff;
  const int nr = (ASCON_AEAD_RATE == 8) ? 6 : 8;
  /* full ciphertext blocks */
  while (clen >= ASCON_AEAD_RATE) {
    ascon_state_t t, u;
    t.z = _mm512_maskz_loadu_epi8(mask, c);
    t.z = _mm512_maskz_shuffle_epi8(mask, t.z, u64big);
    s->z = _mm512_xor_epi64(s->z, t.z);
    u.z = _mm512_maskz_shuffle_epi8(mask, s->z, u64big);
    s->z = _mm512_mask_blend_epi8(mask, s->z, t.z);
    _mm512_mask_storeu_epi8(m, mask, u.z);
    printstate("insert ciphertext", s);
    P(s, nr);
    m += ASCON_AEAD_RATE;
    c += ASCON_AEAD_RATE;
    clen -= ASCON_AEAD_RATE;
  }
  /* final ciphertext block */
  uint64_t* px = &s->x[0];
  if (ASCON_AEAD_RATE == 16 && clen >= 8) {
    uint64_t cx = LOAD(c, 8);
    s->x[0] ^= cx;
    STORE(m, s->x[0], 8);
    s->x[0] = cx;
    px = &s->x[1];
    m += 8;
    c += 8;
    clen -= 8;
  }
  *px ^= PAD(clen);
  if (clen) {
    uint64_t cx = LOADBYTES(c, clen);
    *px ^= cx;
    STOREBYTES(m, *px, clen);
    *px = CLEAR(*px, clen);
    *px ^= cx;
  }
  printstate("pad ciphertext", s);
}

forceinline void ascon_final(ascon_state_t* s, const ascon_key_t* key) {
#if CRYPTO_KEYBYTES == 16
  if (ASCON_AEAD_RATE == 8) {
    s->x[1] ^= key->x[0];
    s->x[2] ^= key->x[1];
  } else {
    s->x[2] ^= key->x[0];
    s->x[3] ^= key->x[1];
  }
#else /* CRYPTO_KEYBYTES == 20 */
  s->x[1] ^= KEYROT(key->x[0], key->x[1]);
  s->x[2] ^= KEYROT(key->x[1], key->x[2]);
  s->x[3] ^= KEYROT(key->x[2], 0);
#endif
  printstate("final 1st key xor", s);
  P(s, 12);
#if CRYPTO_KEYBYTES == 16
  s->x[3] ^= key->x[0];
  s->x[4] ^= key->x[1];
#else /* CRYPTO_KEYBYTES == 20 */
  s->x[3] ^= key->x[1];
  s->x[4] ^= key->x[2];
#endif
  printstate("final 2nd key xor", s);
}

forceinline void ascon_gettag(ascon_state_t* s, uint8_t* t) {
  STOREBYTES(t, s->x[3], 8);
  STOREBYTES(t + 8, s->x[4], 8);
}

forceinline int ascon_verify(ascon_state_t* s, const uint8_t* t) {
  /* verify should be constant time, check compiler output */
  s->x[3] ^= LOADBYTES(t, 8);
  s->x[4] ^= LOADBYTES(t + 8, 8);
  return NOTZERO(s->x[3], s->x[4]);
}

int ascon_aead_encrypt(uint8_t* t, uint8_t* c, const uint8_t* m, uint64_t mlen,
                       const uint8_t* ad, uint64_t adlen, const uint8_t* npub,
                       const uint8_t* k) {
  ascon_state_t s;
  ascon_key_t key;
  ascon_loadkey(&key, k);
  ascon_initaead(&s, &key, npub);
  ascon_adata(&s, ad, adlen);
  ascon_encrypt(&s, c, m, mlen);
  ascon_final(&s, &key);
  ascon_gettag(&s, t);
  return 0;
}

int ascon_aead_decrypt(uint8_t* m, const uint8_t* t, const uint8_t* c,
                       uint64_t clen, const uint8_t* ad, uint64_t adlen,
                       const uint8_t* npub, const uint8_t* k) {
  ascon_state_t s;
  ascon_key_t key;
  ascon_loadkey(&key, k);
  ascon_initaead(&s, &key, npub);
  ascon_adata(&s, ad, adlen);
  ascon_decrypt(&s, m, c, clen);
  ascon_final(&s, &key);
  return ascon_verify(&s, t);
}

int crypto_aead_encrypt(unsigned char* c, unsigned long long* clen,
                        const unsigned char* m, unsigned long long mlen,
                        const unsigned char* ad, unsigned long long adlen,
                        const unsigned char* nsec, const unsigned char* npub,
                        const unsigned char* k) {
  (void)nsec;
  *clen = mlen + CRYPTO_ABYTES;
  return ascon_aead_encrypt(c + mlen, c, m, mlen, ad, adlen, npub, k);
}

int crypto_aead_decrypt(unsigned char* m, unsigned long long* mlen,
                        unsigned char* nsec, const unsigned char* c,
                        unsigned long long clen, const unsigned char* ad,
                        unsigned long long adlen, const unsigned char* npub,
                        const unsigned char* k) {
  (void)nsec;
  if (clen < CRYPTO_ABYTES) return -1;
  *mlen = clen = clen - CRYPTO_ABYTES;
  return ascon_aead_decrypt(m, c + clen, c, clen, ad, adlen, npub, k);
}

#endif