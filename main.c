#include "include/bit_packer.h"
#include "include/debug.h"
#include "include/huffman_tree.h"
#include "include/priority_queue.h"
#include "include/tree_serializer.h"
#include "include/vector.h"
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

FILE *open_file(char *filename, char *mode);
void compress(FILE *, FILE *);
void uncompress(FILE *, FILE *);
vector *read_header(FILE *);
void write_header(huffman_node_t *, FILE *);
void write_file(FILE *, FILE *, vector *);

FILE *open_file(char *filename, char *mode) {
  FILE *fp = fopen(filename, mode);

  if (!fp) {
    puts("Invalid file path: terminating...");
    exit(1);
  }

  return fp;
}

void write_header(huffman_node_t *tree, FILE *fp) {
  tree_serializer *ts = ts_init(fp, tree);
  ts_serialize(ts);
  ts_dispose(ts);
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
  /* hn_print(tree, 2); */
  /* hn_assign_codes(tree, codes); */

  write_header(tree, out);
  /**/
  /* rewind(inp); */
  /* write_file(inp, out, codes); */
  /**/
  /* v_dispose(freq); */
  /* v_dispose(codes); */
}

void write_file(FILE *inp, FILE *out, vector *codes) {
  wchar_t c;

  bit_packer *bp = bp_init(out);
  while (WEOF != (c = getwc(inp))) {
    bp_pack(bp, *v_get(codes, c));
  }

  bp_flush(bp);
  bp_dispose(bp);
}

void uncompress(FILE *inp, FILE *out) { vector *codes = read_header(inp); }

// Stack, queues, heap, hash table, sorting, tree.
vector *read_header(FILE *in) {
  tree_deserializer *ts = ts_init(in, NULL);
  huffman_node_t *tree = ts_deserialize(ts);
  hn_print(tree, 2);
}

int main(int argc, char *argv[argc]) {
  setlocale(LC_ALL, "");
  assert(sizeof(wchar_t) <=
         sizeof(size_t)); // Without this assertion, the program will crash
  if (argc < 4) {
    puts("Invalid Input; Usage: compress INPUT_FILE OPTION[-c|-u] "
         "OUTPUT_FILE\nc: compress, u: uncompress");
    return 1;
  }

  FILE *inp = open_file(argv[1], "rb, ccs=UTF-8");
  FILE *out = open_file(argv[3], "w, ccs=UTF-8");
  if (strcmp(argv[2], "-c") == 0)
    compress(inp, out);
  else if (strcmp(argv[2], "-u") == 0)
    uncompress(inp, out);
  else {
    fclose(inp);
    fclose(out);
    puts("Invalid option");
    return 1;
  }

  fclose(inp);
  fclose(out);
  return EXIT_SUCCESS;
}
