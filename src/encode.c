//
// Created by Don Lasagne on 22.09.25.
//

#include "../include/encode.h"

int encode(encode_args args) {
    //Load Image
    unsigned char** out = NULL;
    unsigned w, h;
    unsigned char* in;
    if (lodepng_decode32_file(out, &w, &h, args->img))
        return 1;

    //Encode into image
    unsigned char bitmask = 8, negative_bitmask = 7;
    unsigned short bitmask_counter = 0, byte_counter = 0, bit_counter = 0;
    unsigned char value = fgetc(args->src);
    while (fgetc(args->src) != EOF) {
        while (bit_counter < 4) {
            for (int i = 0; i < 4; ++i) {
                if (args->bitmask[bitmask_counter]) {
                    bitmask_counter = 0;
                    bitmask = 8;
                    negative_bitmask = 7;
                }
                if (args->bitmask[bitmask_counter] == 1) {
                    *out[byte_counter] = (value & bitmask)>>i & (*out[byte_counter] & negative_bitmask) ;
                    bitmask >>= 1;
                    negative_bitmask = (negative_bitmask >> 1) & 8;
                    byte_counter++;
                    bitmask_counter++;
                    bit_counter++;
                }
            }
        }
        value = fgetc(args->src);
    }

    //Encode Image
    unsigned char** out_image = NULL;
    size_t out_size = 0;
    if (lodepng_encode32(out_image, &out_size,*out, w, h))
        return 2;

    //Write to File
    fwrite(*out_image, out_size, 1, args->out);

    free(out);
    return 0;
}
