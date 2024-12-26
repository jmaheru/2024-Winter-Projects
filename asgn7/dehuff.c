#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 64
struct Node *stack[SIZE];

#define HELP                                                                                       \
    "Usage: ./dehuff -i infile -o outfile\n       ./dehuff -v -i infile -o outfile\n       "       \
    "./dehuff -h\n"

//global var
int top = -1;

//push
void stackpush(struct Node *node) {
    if (top >= SIZE - 1) {
        fprintf(stderr, "The stack's full.\n");
        exit(EXIT_FAILURE);
    }

    stack[++top] = node;
}

//pop
struct Node *stackpop(void) {
    if (top < 0) {
        fprintf(stderr, "The stack's empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack[top--];
}

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    //read uint8_t type1 from inbuf
    uint8_t type1 = bit_read_uint8(inbuf);

    //read uint8_t type2 from inbuf
    uint8_t type2 = bit_read_uint8(inbuf);

    //read uint32_t filesize from inbuf
    uint32_t filesize = bit_read_uint32(inbuf);

    //read uint16_t num_leaves from inbuf
    uint16_t num_leaves = bit_read_uint16(inbuf);

    assert(type1 == 'H');
    assert(type2 == 'C');

    //num_nodes = 2 * num_leaves - 1
    int num_nodes = (2 * num_leaves) - 1;

    //Node *node
    struct Node *node;

    //for i in range(0, num_nodes):
    //	read one bit from inbuf
    //	if bit == 1:
    //		read uint8_t symbol from inbuf
    //		node = node_create(symbol, 0)
    //	else:
    //		node = node_create(0, 0)
    //		node->right = stack_pop()
    //		node->left = stack_pop()
    //	stack_push(node)

    for (int i = 0; num_nodes > i; i++) {

        uint8_t bit = bit_read_bit(inbuf);

        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stackpop();
            node->left = stackpop();
        }

        stackpush(node);
    }

    //Node *code_tree = stack_pop()
    struct Node *code_tree = stackpop();

    //for i in range(0, filesize):
    //	node = code_tree
    //	while true:
    //		read one bit from inbuf
    //		if bit == 0:
    //			node = node->left
    //		else:
    //			node = node->right
    //		if node is a leaf:
    //			break
    //	write uint8 node->symbol to fout

    for (uint32_t j = 0; filesize > j; j++) {
        node = code_tree;
        while (1) {
            uint8_t bit = bit_read_bit(inbuf);
            if (bit != 0) {
                node = node->right;
            } else {
                node = node->left;
            }

            if (node->right == NULL && node->left == NULL) {
                break;
            }
        }

        fputc(node->symbol, fout);
    }

    node_free(&code_tree);
}

int main(int argc, char **argv) {
    FILE *output = NULL;
    BitReader *input = NULL;
    char options[] = "i:o:h";
    int user;

    while (-1 != (user = getopt(argc, argv, options))) {
        switch (user) {
        case 'i':
            input = bit_read_open(optarg);
            if (NULL == input) {
                fprintf(stderr, "dehuff:  error with input file %s\n", optarg);
                fprintf(stderr, HELP);
                exit(1);
            } else {
                break;
            }

        case 'o':
            output = fopen(optarg, "wb");
            if (NULL == output) {
                printf("dehuff:  poorly formatted -o\n");
                exit(1);
            }
            break;

        case 'h': fprintf(stderr, HELP); exit(0);
        }
    }

    if (input == NULL) {
        fprintf(stderr, "dehuff:  -i(input) is required\n");
        fprintf(stderr, HELP);
        exit(1);
    } else if (output == NULL) {
        fprintf(stderr, "dehuff:  -o(output) is required\n");
        fprintf(stderr, HELP);
        exit(1);
    }

    dehuff_decompress_file(output, input);

    fclose(output);
    bit_read_close(&input);

    return 0;
}
