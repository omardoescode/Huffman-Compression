#ifndef BIT_UNPACKER_HEADER
#define BIT_UNPACKER_HEADER
#include "huffman_tree.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct bit_unpacker bit_unpacker;
struct bit_unpacker;

bit_unpacker *bu_init(huffman_node_t *tree, FILE *fp);
void bu_unpack(bit_unpacker *, FILE *out);
void bu_free(bit_unpacker *);
#endif // !BIT_UNPACKER_HEADER
