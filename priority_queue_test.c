#include "include/huffman_tree.h"
#define DEBUG 1

#include "include/priority_queue.h"
#include <assert.h>

int main(void) {
  char_int_priority_queue_t *queue = cihq_init();

  assert(cihq_is_empty(queue));

  huffman_node_t val = {'a', 1};
  huffman_node_t val2 = {'b', 3};
  huffman_node_t val3 = {'c', 2};

  cihq_insert(queue, &val);
  assert(!cihq_is_empty(queue));

  cihq_insert(queue, &val2);
  cihq_insert(queue, &val3);

  huffman_node_t *rem = cihq_delete_min(queue);
  assert(rem->element == 'a' && rem->weight == 1);

  rem = cihq_delete_min(queue);
  assert(rem->element == 'c' && rem->weight == 2);

  rem = cihq_delete_min(queue);
  assert(rem->element == 'a' && rem->weight == 1);

  assert(cihq_is_empty(queue));

  puts("Hooray!!. This has been successful");
  return 0;
}
