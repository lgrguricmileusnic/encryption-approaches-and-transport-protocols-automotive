//
// Created by Lovro Grgurić Mileusnić on 31.07.2024..
//
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

#include "util/util.h"
#include"ascon128v12_ref/crypto_aead.h"
char usage[] = "usage: ";

void ascon_encrypt(char *infile, char *outfile);
void ascon_decrypt(char *infile, char *outfile);

int main(int argc, char *argv[]) {
    int opt;
    int ff = 0, ef = 0, df = 0, hf = 0, of = 0;
    char *filename, *outname;
    while ((opt = getopt(argc, argv, "f:o:edh")) != -1) {
        switch (opt) {
            case 'f':
                ff = 1;
                filename = optarg;
                break;
            case 'h':
                hf = 1;
                break;
            case 'e':
                ef = 1;
                break;
            case 'd':
                df = 1;
                break;
            case 'o':
                of = 1;
                outname = optarg;
                break;
        }
    }

    if (
        (ef && df) ||
        ((ef || df) && (!ff || !of)) ||
        hf
    ) {
        printf("%s\n", usage);
        if (hf)
            exit(0);
        exit(1);
    }

    if (ef) {
        ascon_encrypt(filename, outname);
    }
    else if (df) {
        ascon_decrypt(filename, outname);
    }
}

void ascon_encrypt(char *infile, char *outfile) {
    FILE *fptr, *optr;
    long mlen;
    unsigned char *m;
    unsigned char *c;
    unsigned long long clen;
    unsigned char n[32] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    }; // nonce
    unsigned char k[32] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    }; // key

    printf("Reading file %s...\n", infile);
    fptr = fopen(infile, "r");
    if (fptr == NULL) {
        printf("Couldn't open file %s\n", infile);
        exit(1);
    }
    mlen = fgetsize(fptr);
    m = malloc(mlen);
    c = malloc(mlen);

    if (m == NULL || c == NULL) {
        printf("Error allocating memory for data and ciphertext. \n");
        exit(1);
    }

    fread(m, sizeof(unsigned char), mlen, fptr);
    fclose(fptr);

    printf("Encrypting...\n");
    crypto_aead_encrypt(c, &clen, m, mlen, NULL, 0, (void *) 0, n, k);

    printf("Writing ciphertext to %s\n", outfile);
    optr = fopen(outfile, "w");
    fwrite(c, sizeof(unsigned char), clen, optr);
    fclose(optr);

    free(m);
    free(c);
}

void ascon_decrypt(char *infile, char *outfile) {
    FILE *fptr, *optr;
    long clen;
    int err;
    unsigned char *c;
    unsigned char *m;
    unsigned long long mlen;
    unsigned char n[32] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    }; // nonce
    unsigned char k[32] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    }; // key

    printf("Reading file %s...\n", infile);
    fptr = fopen(infile, "r");
    if (fptr == NULL) {
        printf("Couldn't open file %s\n", infile);
        exit(1);
    }
    clen = fgetsize(fptr);
    c = malloc(clen);
    m = malloc(clen);

    if (c == NULL || m == NULL) {
        printf("Error allocating memory for data or ciphertext. \n");
        exit(1);
    }

    fread(c, sizeof(unsigned char), clen, fptr);
    fclose(fptr);

    printf("Decrypting...\n");
    err = crypto_aead_decrypt(m, &mlen, (void *) 0, c, clen, NULL, 0, n, k);
    if (err) {
        printf("Error during verification.");
        exit(err);
    }
    printf("Writing plaintext to %s\n", outfile);
    optr = fopen(outfile, "w");
    fwrite(m, sizeof(unsigned char), mlen, optr);
    fclose(optr);

    free(c);
    free(m);
}