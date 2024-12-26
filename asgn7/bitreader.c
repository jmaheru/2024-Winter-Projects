#include "bitreader.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    //allocate a new BitReader
    BitReader *read = calloc(1, sizeof(BitReader));
    if (read == NULL) {
        return NULL;
    }
    //open the filename for reading as a binary file, storing the result in FILE *f
    FILE *read_file = fopen(filename, "rb");
    if (read_file == NULL) {
        free(read);
        return NULL;
    }
    //store f in the BitReader field underlying_stream
    read->underlying_stream = read_file;
    //clear the byte field of the BitReader to 0
    read->byte = 0;
    //set the bit_position field of the BitReader to 8
    read->bit_position = 8;

    return read;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        //close the underlying_stream
        if ((fclose((*pbuf)->underlying_stream)) != 0) {
            exit(1);
        }

        free(*pbuf);
        *pbuf = NULL;

        if (*pbuf != NULL) {
            exit(1);
        }
    }
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t b = 0x00000000;
    for (int i = 0; i <= 31; i++) {
        //read a bit b from the underlying_stream
        //set bit i of byte to the value of b
        uint8_t t = bit_read_bit(buf);
        b |= (uint32_t) t << i;
    }
    return b;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t b = 0x0000;
    for (int i = 0; i <= 15; i++) {
        //read a bit b from the underlying_stream
        //set bit i of byte to the value of b
        uint8_t t = bit_read_bit(buf);
        b |= (uint16_t) t << i;
    }
    return b;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t b = 0x00;
    for (int i = 0; i <= 7; i++) {
        //read a bit b from the underlying_stream
        //set bit i of byte to the value of b
        uint8_t t = bit_read_bit(buf);
        b |= (uint8_t) t << i;
    }
    return b;
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        //read a byte from the underlying_stream using fgetc()
        int byte = fgetc(buf->underlying_stream);
        if (byte == EOF) {
            exit(1);
        }
        buf->byte = (uint8_t) byte;
        buf->bit_position = 0;
    }
    //get the bit numbered bit_position from byte

    uint8_t val = ((buf->byte >> buf->bit_position) & 1);
    buf->bit_position++;

    return val;
}
