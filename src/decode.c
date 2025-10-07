#include <decode.h>
#include <lodepng.h>

unsigned int decode(decode_args decode_struct ) {
    unsigned error;
    unsigned char* img = 0;
    unsigned width, height;
    const char* filename = decode_struct->src;

    unsigned char new_byte = 0;
    int bit_idx = 7;
    unsigned int bitmask_len = strlen(decode_struct->bitmask);
    unsigned int bitmask_idx = 0;
    unsigned long read_count = 0;

    error = lodepng_decode32_file(&img, &width, &height, filename);
    if (error) {
        return error;
    }

    for (unsigned int i = 0; i < width * height* 4; i++) { //32 bit pro pixel -> jew 4 (r, g, b, a)
        unsigned char byte = img[i];
        for (int j = 7; j >=0; j--) { // mit j altes byte durchgehen
            if (decode_struct->bitmask[bitmask_idx] == '1') {
                int bit = (byte >> (j)) &1;

                new_byte |= (bit << bit_idx); // neues Byte von links nach rechts schreiben

                bit_idx--;

                if (bit_idx < 0) { //neues Byte voll
                    fwrite(&new_byte,1,1, decode_struct->out);
                    new_byte = 0;
                    bit_idx = 7;
                }
                read_count++;

                if (read_count == decode_struct->length) {
                    free(img);
                    return EXIT_SUCCESS;
                }
            }
            bitmask_idx++;
            if (bitmask_idx >= bitmask_len) {bitmask_idx = 0;}
        }
    }
    free(img);
    return EXIT_SUCCESS;
}
