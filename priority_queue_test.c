#include "include/huffman_tree.h"
#include "include/priority_queue.h"
#include <assert.h>

int main(void) {
  priority_queue_t *queue = cihq_init();

  assert(cihq_is_empty(queue));

  huffman_node_t *val = hn_init('a', 1, 0, 0);
  huffman_node_t *val2 = hn_init('b', 3, 0, 0);
  huffman_node_t *val3 = hn_init('c', 2, 0, 0);

  cihq_insert(queue, val);
  assert(!cihq_is_empty(queue));

  cihq_insert(queue, val2);
  cihq_insert(queue, val3);

  huffman_node_t *rem = cihq_delete_min(queue);
  assert(rem->element == 'b' && rem->weight == 3);

  rem = cihq_delete_min(queue);
  assert(rem->element == 'c' && rem->weight == 2);

  rem = cihq_delete_min(queue);
  assert(rem->element == 'a' && rem->weight == 1);

  assert(cihq_is_empty(queue));

  puts("Hooray!!. This has been successful");
  return 0;
}
