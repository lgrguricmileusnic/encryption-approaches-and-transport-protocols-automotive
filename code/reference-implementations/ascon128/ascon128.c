//
// Created by Lovro Grgurić Mileusnić on 31.07.2024..
//
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#include "util/util.h"
#include"ascon128v12_ref/crypto_aead.h"
char usage[] = "usage: ";

int main(int argc, char *argv[]) {
    int opt;
    int ff = 0, ef = 0, df = 0, hf = 0, of = 0;
    char *filename, *outname;
    FILE* fptr;
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
        ((ef || df) && (!ff || !of))||
        hf
    ) {
        printf("%s\n", usage);
        if (hf)
            exit(0);
        exit(1);
    }

    if (ef) {
        fptr = fopen(filename, "r");
        if(fptr == NULL) {
            printf("Couldn't open file %s", filename);
            exit(1);
        }
        fgetsize(fptr);
        fread(fptr, );
    }
}

void encrypt()