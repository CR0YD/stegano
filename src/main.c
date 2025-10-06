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


    size_t bytes;
    switch (args->mode) {
        case 0:
            if (!encode(args->args.encode, &bytes)) {
                printf("Encode successful!\n");
                printf("%lu bits written\n", bytes);
                break;
            }
            fprintf(stderr, "##ERROR## Could not encode data\n");
            break;
        case 1:
            if (!decode(args->args.decode)) {
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
