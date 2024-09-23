#ifndef HUFFMAN_TREE_HEADER
#define HUFFMAN_TREE_HEADER

#include <stdbool.h>
#include <stdlib.h>
struct char_int_priority_queue_t;
typedef struct char_int_priority_queue_t char_int_priority_queue_t;
/*
 * Invariants:
 *   - '\0' is element for non-leaves
 */

typedef struct huffman_node_t huffman_node_t;
struct huffman_node_t {
  char element;
  int weight;
  huffman_node_t *left;
  huffman_node_t *right;
};

huffman_node_t *hn_init(char el, int wt, huffman_node_t *l, huffman_node_t *r);
void hn_copy(huffman_node_t *dest, const huffman_node_t *src);
bool hn_is_leaf(huffman_node_t *hn);
int hn_compare(const huffman_node_t *v1, const huffman_node_t *v2);
huffman_node_t *hn_combine(huffman_node_t *v1, huffman_node_t *v2);
huffman_node_t *hn_create_tree(char_int_priority_queue_t *chq);
#endif
