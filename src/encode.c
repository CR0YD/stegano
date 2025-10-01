//
// Created by Don Lasagne on 22.09.25.
//

#include "../include/encode.h"

int encode(encode_args args, size_t* len) {
    *len = 0;
    //Load Image
    unsigned char* out;
    unsigned w, h;
    if (lodepng_decode32_file(&out, &w, &h, args->img))
        return 1;

    //Encode into image
    unsigned char bitmask = 128;
    unsigned short bitmask_counter = 0, byte_counter = 0, bit_written_counter = 0, bit_counter = 0;
    char value = (char) fgetc(args->src);
    while (value != EOF && byte_counter < w * h * 4) {
        for (int i = bit_counter; i < 8; i++, bit_counter++) {
            if (args->bitmask[bitmask_counter] == '\0') {
                bitmask_counter = 0;
            }
            if (args->bitmask[bitmask_counter] == '1') {
                unsigned char bit = !!(value & bitmask) ? 1 : 0;
                const unsigned char current_bit  = 7-i;
                bit <<= current_bit;
                out[byte_counter] = bit | (out[byte_counter] & (char) (255 - pow(2,current_bit)));
                bitmask >>= 1;
                bit_written_counter++;
            }
            bitmask_counter++;
            if (bit_written_counter == 8) {
                bit_counter++;
                break;
            }
        }
        if (bit_counter == 8) {
            byte_counter++;
            bit_counter = 0;
        }
        if (bit_written_counter == 8) {
            value = (char) fgetc(args->src);
            bitmask = 128;
            bit_written_counter = 0;
        }
    }
    *len = byte_counter;

    //Encode Image
    unsigned char* out_image;
    size_t out_size = 0;
    if (lodepng_encode32(&out_image, &out_size,out, w, h))
        return 2;

    //Write to File
    fwrite(out_image, out_size, 1, args->out);
    return 0;
}
