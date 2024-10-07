#ifndef BIT_UNPACKER_HEADER
#define BIT_UNPACKER_HEADER
#include "huffman_tree.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct bit_unpacker bit_unpacker;
struct bit_unpacker;

/**
 * @brief Construct a bit unpacker
 *
 * Initalize the buffer and bit position to zero. Set the fields to their
 * corresponding arguments
 *
 * @param tree The tree to use when deserializing
 * @param fp The input file to read from the bytes to unpack
 * @return A pointer to the bit unpacker
 */
bit_unpacker *bu_init(huffman_node_t *tree, FILE *fp);

/**
 * @brief Unpack the input file into the given file
 *
 * Read each bit. If the bit is 0, go left in the tree. If 1, go right. Do
 * recursively until a leaf is encountered. Print the corresponding
 * element/symbol to file and reset the tree to the root
 *
 * @param bu The bit unpacker
 * @param out The file to write to
 * @param char_count The character count in the file
 */
void bu_unpack(bit_unpacker *bu, FILE *out, size_t char_count);

/**
 * @brief free the bit unpacker
 *
 * @param The bit unpacker to free
 */
void bu_free(bit_unpacker *bu);
#endif // !BIT_UNPACKER_HEADER
