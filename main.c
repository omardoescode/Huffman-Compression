#include "include/huffman_tree.h"
#include "include/priority_queue.h"

#include "include/debug.h"
#include "include/vector.h"
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

FILE *open_file(char *filename, char *mode);
void compress(FILE *fp);

FILE *open_file(char *filename, char *mode) {
  FILE *fp = fopen(filename, mode);

  if (!fp) {
    puts("Invalid file path: terminating...");
    exit(1);
  }

  return fp;
}

void compress(FILE *fp) {
  vector *freq = v_init(0);
  vector *codes = v_init(0);

  priority_queue_t *queue = cihq_init();

  wchar_t c;
  while (WEOF != (c = getwc(fp))) {
    /* printf("Read character: %lc, current size: %zu\n", c, */
    /*        v_size(freq)); // Debugging print */
    assert(c >= 0); // Ensure we are not missing around
    v_type *v;
    if ((v = v_get(freq, c))) {
      (*v)++;
    } else {
      v_set(freq, c, 1);
    }
  }

  /* for (int i = 0; i < v_size(freq); i++) { */
  /*   v_type val = *v_get(freq, i); */
  /*   if (val) */
  /*     printf("%lc: %u\n", i, val); */
  /* } */

  // Plug data into priority queue
  for (int i = 0; i < v_size(freq); i++) {
    v_type val = *v_get(freq, i);
    if (!val)
      continue;

    cihq_insert(queue, hn_init(i, val, 0, 0));
  }

  huffman_node_t *tree = hn_create_tree(queue);
  /* hn_print(tree); */

  hn_assign_codes(tree, codes);

  for (int i = 0; i < v_size(codes); i++) {
    v_type val = *v_get(codes, i);
    if (!val)
      continue;
    printf("%c: %#zX\n", i, val);
  }
#if 0
#endif
}

int main(int argc, char *argv[argc]) {
  setlocale(LC_ALL, "");
  if (argc < 2) {
    puts("No File is given to this command");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp = open_file(argv[i], "r, ccs=UTF-8");
    compress(fp);
    fclose(fp);
  }
  return EXIT_SUCCESS;
}
