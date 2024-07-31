//
// Created by Lovro Grgurić Mileusnić on 31.07.2024..
//

#include "util.h"
#include<stdio.h>

long fgetsize (FILE *fptr){
    long cursor = ftell(fptr);
    long fsize;
    fseek(fptr, 0, SEEK_END);
    fsize = ftell(fptr);
    fseek(fptr, cursor, SEEK_SET);
    return fsize;
}