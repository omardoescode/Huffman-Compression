#include "include/bit_packer.h"
#include "include/bit_unpacker.h"
#include "include/debug.h"
#include "include/huffman_tree.h"
#include "include/priority_queue.h"
#include "include/tree_serializer.h"
#include "include/vector.h"
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define HEADER "HUFF"

FILE *open_file(char *filename, char *mode);
void compress(FILE *, FILE *);
void uncompress(FILE *, FILE *);
huffman_node_t *read_header(FILE *);
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
  tree_serializer *ts = ts_init(fp, tree, log2(sizeof(wchar_t)));
  ts_serialize(ts);
  ts_free(ts);
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
    if (val)
      cihq_insert(queue, hn_init(i, val, 0, 0));
  }

  huffman_node_t *tree = hn_create_tree(queue);
  hn_print(tree);
  hn_assign_codes(tree, codes);

  write_header(tree, out);

  rewind(inp);
  write_file(inp, out, codes);

  v_free(freq);
  v_free(codes);
  cihq_free(queue);
  hn_free(tree);
}

void write_file(FILE *inp, FILE *out, vector *codes) {
  wchar_t c;

  bit_packer *bp = bp_init(out);

  while (WEOF != (c = getwc(inp))) {
    wchar_t val = *v_get(codes, c);
    bp_pack(bp, val);
  }

  bp_flush(bp);
  bp_free(bp);
}

void uncompress(FILE *inp, FILE *out) {
  /* char *header = malloc(strlen(HEADER) + 1); */
  /* char count; */
  /* fread(header, strlen(HEADER), 1, inp); */
  /* fread(&count, sizeof(count), 1, inp); */
  /**/
  /* header[strlen(HEADER)] = '\0'; */
  /* assert(strcmp(header, HEADER) == 0); */
  tree_deserializer *ts = ts_init(inp, NULL, log2(sizeof(wchar_t)));

  huffman_node_t *tree = ts_deserialize(ts);
  hn_print(tree);

  bit_unpacker *bu = bu_init(tree, inp);
  bu_unpack(bu, out);

  bu_free(bu);
  ts_free(ts);
  hn_free(tree);
}

int main(int argc, char *argv[argc]) {
  setlocale(LC_ALL, "");
  assert(sizeof(wchar_t) <=
         sizeof(size_t)); // Without this assertion, the program will crash
  if (argc < 4) {
    puts("Invalid Input; Usage: huff INPUT_FILE OPTION[-c|-u] "
         "OUTPUT_FILE\nc: compress, u: uncompress");
    return 1;
  }

  FILE *inp = open_file(argv[1], "rb, ccs=UTF-8");
  FILE *out = open_file(argv[3], "w, ccs=UTF-8");
  if (strcmp(argv[2], "-c") == 0) {
    compress(inp, out);
    puts("Finishied Compression; Enjoy!!");
  } else if (strcmp(argv[2], "-u") == 0) {
    uncompress(inp, out);
    puts("Finishied Uncompression; Enjoy!!");
  } else {
    fclose(inp);
    fclose(out);
    puts("Invalid option");
    return 1;
  }

  fclose(inp);
  fclose(out);
  return EXIT_SUCCESS;
}
