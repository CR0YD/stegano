//
// Created by croyd on 9/15/25.
//

#include <cli.h>
#include <encode.h>
#include <decode.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    cli_args args = get_arguments(argc, argv);

    if (args == NULL) {
        return EXIT_FAILURE;
    }


    switch (args->mode) {
        case 0:
            size_t bytes;
            if (encode(args, &bytes)) {
                printf("Encode successful!\n");
                printf("%lu bytes written\n", bytes);
                break;
            }
            fprintf(stderr, "##ERROR## Could not encode data\n");
            break;
        case 1:
            if (decode(args)) {
                printf("Decode successful!\n");
                break;
            }
            fprintf(stderr, "##ERROR## Could not decode data\n");
            break;
        default:
            break;
    }

    free_cli_args(&args);

    return EXIT_SUCCESS;
}
