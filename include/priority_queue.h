#ifndef PRIORITY_QUEUE_HEADER
#define PRIORITY_QUEUE_HEADER

#include "huffman_tree.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct priority_queue_t priority_queue_t;
struct priority_queue_t;

priority_queue_t *pq_init();
size_t pq_size(priority_queue_t *);
bool pq_is_empty(priority_queue_t *chq);
void pq_bubble_down(priority_queue_t *chq, int hole);
void pq_insert(priority_queue_t *chq, huffman_node_t *value);
huffman_node_t *pq_delete_min(priority_queue_t *chq);
void pq_free(priority_queue_t *);
#endif
