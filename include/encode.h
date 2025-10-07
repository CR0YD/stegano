//
// Created by Don Lasgne on 22.09.25.
//

#ifndef STEGANOGRAPHY_CONFIG_ENCODE_H
#define STEGANOGRAPHY_CONFIG_ENCODE_H
#include <stdio.h>
#include <lodepng.h>
#include <stdlib.h>
#include <cli.h>
#include <math.h>

/**
 *
 * @param args Encode Args struct
 * @param len Length of bits written
 * @return 0 no error, 1 could not load image, 2 could not write to image
 */
int encode(encode_args args, size_t* len);

#endif //STEGANOGRAPHY_CONFIG_ENCODE_H