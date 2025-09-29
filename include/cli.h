//
// Created by croyd on 9/15/25.
//

#ifndef STEGANOGRAPHY_CONFIG_CLI_H
#define STEGANOGRAPHY_CONFIG_CLI_H
#include <stdio.h>

extern char* modesv[];
extern unsigned char modesc;

typedef struct encode_args_struct {
    FILE* src;
    char* img;
    FILE* out;
    char* bitmask;
}* encode_args;

typedef struct decode_args_struct {
    char* src;
    FILE* out;
    char* bitmask;
}* decode_args;

typedef union {
    encode_args encode;
    decode_args decode;
} arg_types;

typedef struct cli_args_struct {
    unsigned mode;
    arg_types args;
}* cli_args;

cli_args get_arguments(int argc, char* argv[]);

void free_cli_args(cli_args* args);

#endif //STEGANOGRAPHY_CONFIG_CLI_H