#ifndef HUFFMAN_TREE_HEADER
#define HUFFMAN_TREE_HEADER

#include "../include/vector.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct priority_queue_t priority_queue_t;
struct priority_queue_t;
/*
 * Invariants:
 *   - '\0' is element for non-leaves
 */

typedef struct huffman_node_t huffman_node_t;
struct huffman_node_t {
  wchar_t element;
  size_t weight;
  huffman_node_t *left;
  huffman_node_t *right;
};

huffman_node_t *hn_init(wchar_t el, size_t wt, huffman_node_t *l,
                        huffman_node_t *r);
void hn_copy(huffman_node_t *dest, const huffman_node_t *src);
bool hn_is_leaf(const huffman_node_t *hn);
int hn_compare(const huffman_node_t *v1, const huffman_node_t *v2);
huffman_node_t *hn_combine(huffman_node_t *v1, huffman_node_t *v2);
huffman_node_t *hn_create_tree(priority_queue_t *chq);
void hn_assign_codes(huffman_node_t *hn, vector *codes);
void hn_print(const huffman_node_t *hn);
void hn_free(huffman_node_t *hn);
#endif
