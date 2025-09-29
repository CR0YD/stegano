//
// Created by Don Lasagne on 22.09.25.
//

#include "../include/encode.h"

int encode(encode_args args, size_t* len) {
    *len = 0;
    //Load Image
    unsigned char* out;
    unsigned w, h;
    //unsigned char* in;
    if (lodepng_decode32_file(&out, &w, &h, args->img))
        return 1;

    //Encode into image
    unsigned char bitmask = 128;
    unsigned short bitmask_counter = 0, byte_counter = 0, bit_written_counter = 0;
    char value = (char) fgetc(args->src);
    while (value != EOF && byte_counter < w * h * 32) {
            for (int i = 0; i < 8; ++i) {
                if (args->bitmask[bitmask_counter] == '\0') {
                    bitmask_counter = 0;
                }
                if (args->bitmask[bitmask_counter] == '1') {
                    unsigned char bit = !!(value & bitmask) ? 1 : 0;
                    bit <<= 7-i;
                    out[byte_counter] = bit | (out[byte_counter] & (unsigned char) (255 - pow(2,7-i)));
                    bitmask >>= 1;
                    bit_written_counter++;
                }
                bitmask_counter++;
                if (bit_written_counter == 7)
                    break;
            }
        byte_counter++;
        if (bit_written_counter == 7) {
            value = (char) fgetc(args->src);
            bit_written_counter = 0;
            bitmask = 128;
            bitmask_counter = 0;
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
