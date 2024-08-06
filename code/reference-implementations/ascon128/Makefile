CC = /usr/bin/clang

# Release
CFLAGS = -march=native -O3

# Debug symbols
CFLAGS = -march=native -g -O3

# Debug symbols and print state
#CFLAGS = -march=native -g -O3 -DASCON_PRINT_STATE
ASCON_SOURCES := $(wildcard ascon128v12_ref/*.c)
ASCON_HEADERS := $(wildcard ascon128v12_ref/*.h)


ascon128: ascon128.c ascon128v12_ref/aead.o util/util.o ascon128v12_ref/printstate.o


all: ascon128

clean:
	@rm -fdr ascon128 *.dSYM ascon128v12_ref/*.o ascon128v12_ref/*.dSYM ascon128v12_ref/*.gch