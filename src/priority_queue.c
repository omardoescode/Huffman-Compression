#include "../include/priority_queue.h"
#include "../include/debug.h"
#include "../include/huffman_tree.h"
#include <limits.h>

priority_queue_t *cihq_init() {
  priority_queue_t *i = (priority_queue_t *)malloc(sizeof(priority_queue_t));
  i->items = hn_init_array(CHAR_MAX);
  i->size = 0;
  return i;
}

bool cihq_is_empty(priority_queue_t *chq) { return chq->size == 0; }
void cihq_bubble_down(priority_queue_t *chq, int hole) {
  int child;
  huffman_node_t *temp = hn_init('\0', 0, 0, 0);
  hn_copy(temp, hn_array_get(chq->items, hole));

  for (; hole * 2 <= chq->size; hole = child) {
    child = hole * 2;

    if (child != chq->size && hn_compare(hn_array_get(chq->items, child + 1),
                                         hn_array_get(chq->items, child)) == -1)
      child++;

    if (hn_compare(hn_array_get(chq->items, child + 1), temp) == -1) {
      hn_copy(hn_array_get(chq->items, hole), hn_array_get(chq->items, child));
    } else
      break;
  }

  hn_copy(hn_array_get(chq->items, hole), temp);
}

void cihq_insert(priority_queue_t *chq, huffman_node_t *value) {
  size_t hole = ++chq->size;
  hn_copy(hn_array_get(chq->items, 0), value);

  for (; hn_compare(value, hn_array_get(chq->items, hole / 2)) == -1; hole /= 2)
    hn_copy(hn_array_get(chq->items, hole), hn_array_get(chq->items, hole / 2));

  hn_copy(hn_array_get(chq->items, hole), hn_array_get(chq->items, 0));
}

huffman_node_t *cihq_delete_min(priority_queue_t *chq) {
  if (cihq_is_empty(chq)) {
    puts("Invalid operation: Priortity queue is empty");
    exit(1);
  }

  huffman_node_t *max_item = hn_init('\0', 0, 0, 0);
  hn_copy(max_item, hn_array_get(chq->items, 1));
  hn_copy(hn_array_get(chq->items, 1), hn_array_get(chq->items, chq->size));
  chq->size--;
  cihq_bubble_down(chq, 1);

  return max_item;
}

void cihq_free(priority_queue_t *chq) { free(chq); }
