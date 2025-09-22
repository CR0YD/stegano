//
// Created by croyd on 9/15/25.
//

#include <cli.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    cli_args args = get_arguments(argc, argv);

    if (args == NULL) {
        return EXIT_FAILURE;
    }

    free_cli_args(&args);

    return EXIT_SUCCESS;
}
