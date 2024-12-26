#include "bitwriter.h"

#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    FILE *newfile = fopen(filename, "wb");
    BitWriter *new = calloc(1, sizeof(BitWriter));

    new->underlying_stream = newfile;
    new->byte = 0;
    new->bit_position = 0;

    if (newfile == NULL || new == NULL || new->underlying_stream != newfile || new->byte != 0
        || new->bit_position != 0) {
        return NULL;
    } else {
        return new;
    }
}

void bit_write_close(BitWriter **pbuf) {
    if (*pbuf != NULL) {
        if ((*pbuf)->bit_position > 0) {
            /* (*pbuf)->byte contains at least one bit that has not yet been written */
            // write the byte to the underlying_stream using fputc()
            int t = fputc((*pbuf)->byte, (*pbuf)->underlying_stream);
            if (t == EOF) {
                exit(1);
            }
        }
        //close the underlying_stream
        if (fclose((*pbuf)->underlying_stream) != 0) {
            exit(1);
        }

        //free the BitWriter
        free(*pbuf);
        *pbuf = NULL;
    }
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if ((buf->bit_position) > 7) {
        //write the byte to the underlying_stream using fputc()
        fputc(buf->byte, buf->underlying_stream);
        //clear the byte and bit_position fields of the BitWriter to zero
        buf->byte = 0;
        buf->bit_position = 0;
    }
    //set the bit at bit_position of the byte to the value of bit
    buf->byte |= (bit & 1) << buf->bit_position;
    buf->bit_position += 1;
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i <= 15; i++) {
        //write bit i of x using bit_write_bit()
        uint8_t val = (x >> i) & 1;
        bit_write_bit(buf, val);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i <= 31; i++) {
        //write bit i of x using bit_write_bit()
        uint8_t val = (x >> i) & 1;
        bit_write_bit(buf, val);
    }
}

void bit_write_uint8(BitWriter *buf, uint8_t byte) {
    for (int i = 0; i <= 7; i++) {
        //write bit i of x using bit_write_bit()
        uint8_t val = (byte >> i) & 1;
        bit_write_bit(buf, val);
    }
}
