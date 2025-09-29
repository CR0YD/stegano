//
// Created by Don Lasgne on 22.09.25.
//

#ifndef STEGANOGRAPHY_CONFIG_ENCODE_H
#define STEGANOGRAPHY_CONFIG_ENCODE_H
#include <stdio.h>
#include <lodepng.h>
#include <stdlib.h>

typedef struct {
    FILE* src;
    char* img;
    FILE* out;
    char* bitmask;
}* encode_args;

int encode(encode_args args);

#endif //STEGANOGRAPHY_CONFIG_ENCODE_H