#include "include/debug.h"
#include "include/huffman_tree.h"
#include "include/priority_queue.h"
#include "include/vector.h"
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define HEADER_END "\0"
FILE *open_file(char *filename, char *mode);
void compress(FILE *, FILE *);
void write_header(vector *, FILE *);
void write_file(FILE *, FILE *, vector *);

FILE *open_file(char *filename, char *mode) {
  FILE *fp = fopen(filename, mode);

  if (!fp) {
    puts("Invalid file path: terminating...");
    exit(1);
  }

  return fp;
}

// TODO: Fix when the input file is empty
// It results in an error
void compress(FILE *inp, FILE *out) {
  vector *freq = v_init(0);
  vector *codes = v_init(0);

  priority_queue_t *queue = cihq_init();
  assert(queue);

  wchar_t c;
  while (WEOF != (c = getwc(inp))) {
    assert(c >= 0); // Ensure we are not missing around
    v_type *v;
    if ((v = v_get(freq, c))) {
      (*v)++;
    } else {
      v_set(freq, c, 1);
    }
  }
  // Make sure '\0' is not used
  assert(*v_get(freq, '\0') == 0);

  // Plug data into priority queue
  for (size_t i = 0; i < v_size(freq); i++) {
    v_type val = *v_get(freq, i);
    if (!val)
      continue;

    cihq_insert(queue, hn_init(i, val, 0, 0));
  }

  huffman_node_t *tree = hn_create_tree(queue);

  hn_assign_codes(tree, codes);

  write_header(codes, out);

  rewind(inp);
  write_file(inp, out, codes);

  v_dispose(freq);
  v_dispose(codes);
}

void write_header(vector *codes, FILE *out) {
  fprintf(out, "%zu\n", v_size(codes) - 1);
  for (size_t i = 0; i < v_size(codes); i++) {
    v_type val = *v_get(codes, i);
    if (val)
      fprintf(out, "%zu %#zX\n", i, val);
  }
}

void write_file(FILE *inp, FILE *out, vector *codes) {
  wchar_t c;
  while (WEOF != (c = getwc(inp))) {
    fprintf(out, "%#zX ", *v_get(codes, c));
  }
}

int main(int argc, char *argv[argc]) {
  setlocale(LC_ALL, "");
  assert(sizeof(wchar_t) <=
         sizeof(size_t)); // Without this assertion, the program will crash
  if (argc < 3) {
    puts("Invalid Input; Usage: compress INPUT_FILE OUTPUT_FILE");
    return 1;
  }

  FILE *inp = open_file(argv[1], "r, ccs=UTF-8");
  FILE *out = open_file(argv[2], "w, ccs=UTF-8");
  compress(inp, out);
  fclose(inp);
  fclose(out);
  return EXIT_SUCCESS;
}
