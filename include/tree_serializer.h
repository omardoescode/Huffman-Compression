#ifndef TREE_SERIALZIER_HEADER
#define TREE_SERIALZIER_HEADER

#include "huffman_tree.h"
#include <stdio.h>
typedef struct tree_serializer tree_serializer;
typedef struct tree_serializer tree_deserializer;
struct tree_serializer;

/**
 * @brief Construct a tree serializer/deserialzer
 *
 * Initalize the buffer and bit count with 0, and set the parameter values to
 * their corresponding memebers
 *
 * @param fp is the file to write to for serialization or read from for
 * deserialization
 * @param tree The tree used for serialization/deserialization
 * @param count The maxmimum count of bytes
 * @return A pointer to the tree
 */
tree_serializer *ts_init(FILE *fp, huffman_node_t *tree, char count);

/**
 * @brief Serialize a tree into the fp
 *
 * Serialization is done like following:
 *  For internal nodes: 0
 *  For nodes: Place 1XXYYYY...Where XX is element-length (field member) long
 * and binary for the number of bytes for the element. YYYY... are the bytes
 * that represent the element (symbol)
 *
 * @param ts The tree serializer
 */
void ts_serialize(tree_serializer *ts);

/**
 * @brief deserialize the file header and construct the corresponding huffman
 * tree
 *
 * Deserailization is done like following
 *  When encountering 0: Build an internal node and recursively get the left and
 * right children When encountering 1: Build a leaf with element that correspond
 * to the next bytes.
 *
 * @param ts: The tree deserializer
 */
huffman_node_t *ts_deserialize(tree_serializer *ts);

/**
 * @brief Free the tree serializer/deserialzer
 *
 * @param ts The tree serializer to free
 */
void ts_free(tree_serializer *);
#endif // !TREE_SERIALZIER_HEADER
