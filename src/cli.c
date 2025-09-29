//
// Created by croyd on 9/15/25.
//
#include <cli.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char* modesv[] = {"encode", "decode"};
unsigned char modesc = 2;

int parse_mode(const char* mode) {
    for (unsigned char i = 0; i < modesc; i++) {
        if (strcmp(mode, modesv[i]) == 0) {
            return i;
        }
    }

    return -1;
}

int validate_bitmask(char* bitmask) {
    for (unsigned i = 0; i < strlen(bitmask); i++) {
        if (bitmask[i] != '0' && bitmask[i] != '1') {
            return -1;
        }
    }

    return 0;
}


void free_encode_args(encode_args* args) {
    if (!args || !*args) {
        return;
    }

    if ((*args)->src) {
        fclose((*args)->src);
    }

    if ((*args)->img) {
        free((*args)->img);
    }

    if ((*args)->out) {
        fclose((*args)->out);
    }

    if ((*args)->bitmask) {
        free((*args)->bitmask);
    }

    free(*args);

    *args = NULL;
}

void free_decode_args(decode_args* args) {
    if (!args || !*args) {
        return;
    }

    if ((*args)->src) {
        free((*args)->src);
    }

    if ((*args)->out) {
        fclose((*args)->out);
    }

    if ((*args)->bitmask) {
        free((*args)->bitmask);
    }

    free(*args);

    *args = NULL;
}

void free_cli_args(cli_args* args) {
    if (!args || !*args) {
        return;
    }

    if ((*args)->mode == 0) {
        free_encode_args(&(*args)->args.encode);
    }

    if ((*args)->mode == 1) {
        free_decode_args(&(*args)->args.decode);
    }

    free(*args);

    *args = NULL;
}

encode_args parse_encode_arguments(int argc, char* argv[]) {
    if (argc < 3) {
        return NULL;
    }

    encode_args args = calloc(1, sizeof(struct encode_args_struct));
    if (args == NULL) {
        return args;
    }

    int offset = 2;

    if (strcmp(argv[offset], "-b") == 0 && argc > offset + 1) {
        if (validate_bitmask(argv[++offset]) != 0) {
            free_encode_args(&args);
            return NULL;
        }

        args->bitmask = calloc(strlen(argv[offset]), sizeof(char));
        strcpy(args->bitmask, argv[offset]);
        offset++;
    }

    if (args->bitmask == NULL) {
        args->bitmask = "00000011";
    }

    if (argc > offset) {
        FILE* src = fopen(argv[offset], "rb");
        if (!src) {
            free_encode_args(&args);
            return NULL;
        }

        args->src = src;
        offset++;
    } else {
        free_encode_args(&args);
        return NULL;
    }

    if (argc > offset) {
        FILE* img = fopen(argv[offset], "r");
        if (!img) {
            free_encode_args(&args);
            return NULL;
        }
        fclose(img);

        args->img = calloc(strlen(argv[offset]), sizeof(char));
        strcpy(args->img, argv[offset]);
        offset++;
    } else {
        free_encode_args(&args);
        return NULL;
    }

    if (argc > offset) {
        FILE* out = fopen(argv[offset], "r");
        if (out || errno == EISDIR) {
            fclose(out);
            free_encode_args(&args);
            return NULL;
        }

        args->out = fopen(argv[offset], "wb");
        offset++;
    } else {
        free_encode_args(&args);
        return NULL;
    }

   if (argc > offset) {
       free_encode_args(&args);
       return NULL;
   }

    return args;
}

decode_args parse_decode_arguments(int argc, char* argv[]) {
    if (argc < 3) {
        return NULL;
    }

    decode_args args = calloc(1, sizeof(struct decode_args_struct));
    if (args == NULL) {
        return args;
    }

    int offset = 2;

    if (strcmp(argv[offset], "-b") == 0 && argc > offset + 1) {
        if (validate_bitmask(argv[++offset]) != 0) {
            free_decode_args(&args);
            return NULL;
        }

        args->bitmask = calloc(strlen(argv[offset]), sizeof(char));
        strcpy(args->bitmask, argv[offset]);
        offset++;
    }

    if (args->bitmask == NULL) {
        args->bitmask = "00000011";
    }

    if (strcmp(argv[offset], "-l") == 0 && argc > offset + 1) {
        args->length = 0;
        for (unsigned i = 0; i < strlen(argv[offset + 1]); i++) {
            if (argv[offset + 1][i] - '0' < 0 || argv[offset + 1][i] - '9' > 0) {
                fprintf(stderr, "##ERROR## Invalid number for option [-l].\n");
                free_decode_args(&args);
                return NULL;
            }
            args->length = args->length * 10 + (argv[offset + 1][i] - '0');
        }

        offset++;
    } else {
        fprintf(stderr, "##ERROR## Option [-l] missing.\n");
        free_decode_args(&args);
        return NULL;
    }

    if (argc > offset) {
        FILE* src = fopen(argv[offset], "r");
        if (!src) {
            free_decode_args(&args);
            return NULL;
        }
        fclose(src);

        args->src = calloc(strlen(argv[offset]), sizeof(char));
        strcpy(args->src, argv[offset]);
        offset++;
    } else {
        free_decode_args(&args);
        return NULL;
    }

    if (argc > offset) {
        FILE* out = fopen(argv[offset], "r");
        if (out || errno == EISDIR) {
            fclose(out);
            free_decode_args(&args);
            return NULL;
        }

        args->out = fopen(argv[offset++], "wb");
    } else {
        free_decode_args(&args);
        return NULL;
    }

    if (argc > offset) {
        free_decode_args(&args);
        return NULL;
    }

    return args;
}

arg_types parse_arguments(int argc, char* argv[], unsigned mode) {
    arg_types types;
    switch (mode) {
        case 0:
            types.encode = parse_encode_arguments(argc, argv);
            break;
        case 1:
            types.decode = parse_decode_arguments(argc, argv);
            break;
        default:
            types.encode = NULL;
    }

    return types;
}

cli_args get_arguments(int argc, char* argv[]) {
    if (argc < 2) {
        return NULL;
    }

    cli_args args = calloc(1, sizeof(struct cli_args_struct));
    if (args == NULL) {
        return args;
    }

    args->mode = -1;

    const int mode = parse_mode(argv[1]);

    if (mode == -1) {
        free_cli_args(&args);
        return NULL;
    }

    args->mode = (unsigned) mode;

    args->args = parse_arguments(argc, argv, mode);

    if (args->args.decode == NULL && args->args.encode == NULL) {
        free_cli_args(&args);
        return NULL;
    }

    return args;
}