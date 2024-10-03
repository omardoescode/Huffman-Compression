#ifndef TREE_SERIALZIER_HEADER
#define TREE_SERIALZIER_HEADER

#include "huffman_tree.h"
#include <stdio.h>
typedef struct tree_serializer tree_serializer;
typedef struct tree_serializer tree_deserializer;
struct tree_serializer;

tree_serializer *ts_init(FILE *fp, huffman_node_t *tree);
void ts_free(tree_serializer *);
void ts_serialize(tree_serializer *);
huffman_node_t *ts_deserialize(tree_serializer *);
void ts_dispose(tree_serializer *);
#endif // !TREE_SERIALZIER_HEADER
