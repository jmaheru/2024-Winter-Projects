#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

#define HELP                                                                                       \
    "Usage: ./huff -i infile -o outfile\n       ./huff -v -i infile -o outfile\n       ./huff "    \
    "-h\n"

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    if (histogram == NULL) {
        exit(0);
    }

    int tv;
    uint32_t file = 0;

    //ensure values are all 0
    for (int i = 0; 256 > i; i++) {
        histogram[i] = 0;
    }

    histogram[0x00]++;
    histogram[0xFF]++;

    //update tv
    while ((tv = fgetc(fin)) != EOF) {
        histogram[tv]++;
        file++;
    }

    return file;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    if (num_leaves == NULL || histogram == NULL) {
        return NULL;
    }

    *num_leaves = 0;

    PriorityQueue *queue = pq_create();
    if (queue == NULL) {
        return NULL;
    }
    //Go through the histogram, and create a node for every non-zero histogram entry.
    //Write the number of nodes added to the Priority Queue to *num_leaves.
    //Initialize each node with the symbol and weight of its histogram entry.
    //Put each node in the priority queue.

    int i = 0;
    while (i < 256) {
        if (histogram[i] != 0) {

            Node *new = node_create((uint8_t) i, histogram[i]);

            if (new == NULL) {
                pq_free(&queue);
            }

            enqueue(queue, new);
            (*num_leaves)++;
        }

        i++;
    }

    //while Priority Queue has more than one entry
    //Dequeue into left
    //Dequeue into right
    //Create a new node with symbol = 0 and weight = left->weight + right->weight
    //node->left = left
    //node->right = right
    //Enqueue the new node

    while (pq_size_is_1(queue) == false && pq_is_empty(queue) == false) {
        Node *left = dequeue(queue);
        Node *right = dequeue(queue);
        Node *new2 = node_create(0, left->weight + right->weight);

        if (new2 == NULL) {
            pq_free(&queue);
            return NULL;
        }

        new2->left = left, new2->right = right;
        enqueue(queue, new2);
    }

    Node *tree = dequeue(queue);
    pq_free(&queue);

    return tree;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left == NULL || node->right == NULL) {
        /* Leaf node: store the Huffman Code. */
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    } else {
        /* Recursive calls left and right. 
		   append a 0 to code and recurse 
		   (don't neeed to append a 0; it's already there) */

        fill_code_table(code_table, node->left, code, code_length + 1);

        //append a 1 to code and recurse
        code |= (uint64_t) 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        /* node is a leaf */
        //write bit 1 to outbuf
        //write uint8 node->symbol to outbuf

        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        /* node is internal */

        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);

        //write bit 0 to outbuf
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    //write uint8_t 'H' to outbuf
    bit_write_uint8(outbuf, 'H');
    //write uint8_t 'C' to outbuf
    bit_write_uint8(outbuf, 'C');
    //write uint32_t filesize to outbuf
    bit_write_uint32(outbuf, filesize);
    //write uint16_t num_leaves to outbuf
    bit_write_uint16(outbuf, num_leaves);
    //huff_write_tree(outbuf, code_tree)
    huff_write_tree(outbuf, code_tree);

    //while true:
    //	b = fgetc(fin)
    //	if b == EOF:
    //		break
    //	code = code_table[b].code
    //	code_length = code_table[b].code_length
    //	for i in range(0, code_length):
    //		write bit (code & 1) to outbuf
    //		code >>= 1

    while (1) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }

        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;

        for (int i = 0; code_length > i; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
}

int main(int argc, char **argv) {
    FILE *input = NULL;
    BitWriter *output = NULL;

    char options[] = "i:o:h";
    int user;
    while (-1 != (user = getopt(argc, argv, options))) {
        switch (user) {
        case 'i':
            input = fopen(optarg, "rb");
            if (NULL == input) {
                fprintf(stderr, "huff:  error with input file %s\n", optarg);
                fprintf(stderr, HELP);
                exit(1);
            } else {
                break;
            }

        case 'o':
            output = bit_write_open(optarg);
            if (NULL == output) {
                printf("huff: poorly formatted -o\n");
                exit(1);
            }
            break;

        case 'h': fprintf(stderr, HELP); exit(0);
        }
    }

    if (input == NULL) {
        fprintf(stderr, "huff:  -i(input) is required\n");
        fprintf(stderr, HELP);
        exit(1);
    } else if (output == NULL) {
        fprintf(stderr, "huff:  -o(output) is required\n");
        fprintf(stderr, HELP);
        exit(1);
    }

    uint16_t petals = 0;
    uint32_t *hist = calloc(256, sizeof(uint32_t));
    uint32_t file = fill_histogram(input, hist);

    Node *tree = create_tree(hist, &petals);
    Code *code_table = calloc(256, sizeof(Code));
    fill_code_table(code_table, tree, 0, 0);

    fseek(input, 0, SEEK_SET);

    huff_compress_file(output, input, file, petals, tree, code_table);

    free(hist);
    free(code_table);
    node_free(&tree);
    bit_write_close(&output);
    fclose(input);

    return 0;
}
