#include "include/huffman_tree.h"
#include "include/priority_queue.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Test this compression
void compress(char *filename) {
  unsigned long freq[CHAR_MAX + 1];
  memset(freq, 0, sizeof(freq));
  FILE *fp = fopen(filename, "r");
  char_int_priority_queue_t queue;

  char c;
  while (EOF != (c = getc(fp))) {
    freq[c]++;
  }

  // Plug data into priority queue

  for (int i = 0; i <= CHAR_MAX; i++) {
    if (!freq[i])
      continue;
    cihq_insert(&queue, hn_init(i, freq[i], 0, 0));
  }

  huffman_node_t *tree = hn_create_tree(&queue);
}
int main(int argc, char *argv[argc]) {
  if (argc < 2) {
    puts("No File is given to this command");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    compress(argv[1]);
  }
  return EXIT_SUCCESS;
}
