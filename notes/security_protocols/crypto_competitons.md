### NIST Lightweight Cryptography Standardization Candidates
- AEAD
- selection process, benchmarks, winners
	- https://nvlpubs.nist.gov/nistpubs/ir/2023/NIST.IR.8454.pdf

- NIST LWC implementations
	https://cryptography.gmu.edu/athena/index.php?id=LWC
	https://cryptography.gmu.edu/athena/LWC/LWC_Finalists_protected_SW_implementations.html

1. **ASCON**  (winner, selected for standardization)
	 - https://csrc.nist.gov/news/2023/lightweight-cryptography-nist-selects-ascon
    - **Type**: Authenticated encryption with associated data (AEAD)
	- **Implementation**: 
		- https://github.com/ascon/ascon-c  ^33f503
			- compiled binary: 0.7kB to 4.3kB
				*For instance, if no associated data is present, Ascon-128 can encrypt plaintexts strictly smaller than 8 bytes and Ascon-128a can encrypt plaintexts strictly smaller than 16 bytes with just two calls to the permutation pa. Preliminary software performance results for several short messages and platforms are also shown in Table 19a and Table 19b.*
		- https://github.com/ascon/simpleserial-ascon/releases/tag/v1.2.6
			- alternative
	- https://crypto.stackexchange.com/questions/67683/caesar-finalists-lightweight-case-ascon-vs-acorn
		- better for short messages (CAN)
	- AD + Nonce = 32B (128b + 128b) (half of CAN FD packet) 
2. others:
	1. Grain-128AEAD 
		-  https://grain-128aead.github.io/
		- nonce + tag = 96b + 64b = 20 B 
	2. Elephant was not considered because of bad performance in comparison with AES-GCM, but has small tag and nonce lenght of combined 20B
	2. TinyJAMBU
		-  https://github.com/rweather/TinyJAMBU
		- nonce + tag = 96b + 64b = 20 B 

### eSTREAM Project Finalists
https://competitions.cr.yp.to/estream.html
https://www.ecrypt.eu.org/stream/index.html
- stream ciphers
1. **Grain**
    - **Type**: Stream cipher
	- len(IV) = 64b = 10B 
1. **Trivium**
    - **Type**: Stream cipher
	- len(IV) = 80b = 10B 
2. MICKEY 2.0 (also MICKEY-128 v2)
	- https://www.ecrypt.eu.org/stream/e2-mickey.html
	- len(IV) = 80b = 10B 

### CAESAR Competition Finalists
https://competitions.cr.yp.to/caesar-submissions.html

1. **ACORN**
    - **Type**: Stream cipher-based authenticated encryption
    - **Implementations:
	    - https://github.com/testter2/Acorn/blob/master/acorn128v3/ref/encrypt.c
	    - https://www3.ntu.edu.sg/home/wuhj/research/caesar/caesar.html
			- https://www3.ntu.edu.sg/home/wuhj/research/caesar/finalist_code/acorn128v3_code.zip
	- len(tag + iv) = 16B + 16B = 32
1. ASCON [[crypto_competitons#^33f503]]

### ISO/IEC 29192 Lightweight Cryptography Standards

block iso standard
- https://cdn.standards.iteh.ai/samples/78477/eeb8160165e94018828239d3fc6478a3/ISO-IEC-29192-2-2019.pdf


- pogledaj ovo za popis sifri
	- https://csrc.nist.gov/CSRC/media/Presentations/nist-lwc-standardization/images-media/session1-turan-update-on-nist-lwc-standardization.pdf


![[block_ciphers_iso.png]]
1. **PRESENT**
	https://www.ripublication.com/ijaer17/ijaerv12n19_13.pdf
	https://github.com/kurtfu/present
	https://github.com/Pepton21/present-cipher
3. **CLEFIA**
![[ISO_IEC_stream.png]]

![[ISO_IEC_MAC.png]]

