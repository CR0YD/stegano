#ifndef DECODE_H
#define DECODE_H

#include "stdio.h"
#include "stdlib.h"
#include <cli.h>

/**
 * decodes the data stored in decode_struct->src with decode_struct->bitmask and stores it in decode_struct->out,
 * reads and writes from left to right, max. input length bits
 * @param decode_struct src, out, bitmask, input length from CLI
 * @return 0 if success, else error
 */
unsigned int decode(decode_args decode_struct);
      #endif //DECODE_H
