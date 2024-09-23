#include "../include/priority_queue.h"
#include "../include/debug.h"
#include "../include/huffman_tree.h"

char_int_priority_queue_t *cihq_init() {
  char_int_priority_queue_t *i =
      (char_int_priority_queue_t *)malloc(sizeof(char_int_priority_queue_t));
  i->size = 0;
  return i;
}
bool cihq_is_empty(char_int_priority_queue_t *chq) { return chq->size == 0; }
void cihq_bubble_down(char_int_priority_queue_t *chq, int hole) {
  int child;
  huffman_node_t temp = chq->items[hole];

  for (; hole * 2 <= chq->size; hole = child) {
    child = hole * 2;

    if (child != chq->size &&
        hn_compare(&chq->items[child + 1], &chq->items[child]) == 1)
      child++;

    if (hn_compare(&chq->items[child + 1], &chq->items[child]) == 1) {
      hn_copy(&chq->items[hole], &chq->items[child]);
    } else
      break;
  }

  hn_copy(&chq->items[hole], &temp);
}

void cihq_insert(char_int_priority_queue_t *chq, huffman_node_t *value) {
  unsigned int hole = ++chq->size;
  hn_copy(&chq->items[0], value);

  for (; hn_compare(value, &chq->items[hole / 2]) == 1; hole /= 2)
    hn_copy(&chq->items[hole], &chq->items[hole / 2]);

  hn_copy(&chq->items[hole], &chq->items[0]);

  debug_s("The new list: ");
  for (int i = 1; i <= chq->size; i++) {
    debug_c(' ');
    debug_c(chq->items[i].first);
  }
  debug_c('\n');
}

huffman_node_t *cihq_delete_min(char_int_priority_queue_t *chq) {
  if (cihq_is_empty(chq)) {
    puts("Invalid operation: Priortity queue is empty");
    exit(1);
  }

  huffman_node_t *temp;
  hn_copy(temp, &chq->items[1]);
  hn_copy(&chq->items[1], &chq->items[chq->size--]);
  cihq_bubble_down(chq, 1);

  return temp;
}
