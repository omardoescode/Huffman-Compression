#ifndef PRIORITY_QUEUE_HEADER
#define PRIORITY_QUEUE_HEADER

#include "huffman_tree.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct char_int_priority_queue_t char_int_priority_queue_t;
struct char_int_priority_queue_t {
  huffman_node_t items[CHAR_MAX];
  unsigned int size;
};

char_int_priority_queue_t *cihq_init();
bool cihq_is_empty(char_int_priority_queue_t *chq);
void cihq_bubble_down(char_int_priority_queue_t *chq, int hole);
void cihq_insert(char_int_priority_queue_t *chq, huffman_node_t *value);
huffman_node_t *cihq_delete_min(char_int_priority_queue_t *chq);
#endif
