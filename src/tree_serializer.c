#include "../include/tree_serializer.h"
#include "../include/huffman_tree.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

size_t count_bytes(size_t value, int size) {
  int res = 0;
  for (int i = 0; i < size; i++) {
    value >>= 8;
    if (value == 0)
      return res;
    res++;
  }
  return res;
}

struct tree_serializer {
  char buffer;
  size_t bit_count;
  FILE *fp;
  huffman_node_t *tree;
  unsigned char element_length;
};

void ts_write_bit(tree_serializer *ts, int bit) {
  ts->buffer <<= 1;
  ts->buffer += bit;
  ts->bit_count++;

  if (ts->bit_count == 8) {
    if (fwrite(&ts->buffer, 1, sizeof(ts->buffer), ts->fp) != 1) {
      puts("Could't write");
      exit(1);
    }
    ts->buffer = 0;
    ts->bit_count = 0;
  }
}

void ts_write_multiple_bits(tree_serializer *ts, int bits, int count) {
  for (int i = 0; i < count; i++) {
    ts_write_bit(ts, (bits >> (count - i - 1)) & 1);
  }
}

void ts_write_flush(tree_serializer *ts) {

  if (ts->bit_count) {
    ts->buffer <<= (8 - ts->bit_count);
    if (fwrite(&ts->buffer, 1, sizeof(ts->buffer), ts->fp) != 1) {
      puts("Couldn't write");
      exit(1);
    }
    ts->bit_count = 0;
    ts->buffer = 0;
  }
}

tree_serializer *ts_init(FILE *fp, huffman_node_t *tree, char count) {
  tree_serializer *ts = (tree_serializer *)malloc(sizeof(tree_serializer));
  ts->buffer = 0;
  ts->bit_count = 0;
  ts->fp = fp;
  ts->tree = tree;
  ts->element_length = count;

  return ts;
}

void ts_serialize_aux(tree_serializer *ts, huffman_node_t *tree) {
  if (!tree) {
    ts_write_bit(ts, 1);
    return;
  }

  if (hn_is_leaf(tree)) {
    char count = count_bytes(hn_element(tree), sizeof(hn_element(tree)));

    ts_write_bit(ts, 1);
    ts_write_multiple_bits(ts, count, ts->element_length);

    ts_write_multiple_bits(ts, hn_element(tree), (count + 1) * 8);
    return;
  }

  ts_write_bit(ts, 0);
  ts_serialize_aux(ts, hn_left(tree));
  ts_serialize_aux(ts, hn_right(tree));
}

void ts_serialize(tree_serializer *ts) {
  ts_serialize_aux(ts, ts->tree);
  ts_write_flush(ts);
}

int ts_read_bit(tree_serializer *ts) {
  if (ts->bit_count == 8) {
    if (fread(&ts->buffer, 1, sizeof(ts->buffer), ts->fp) != 1) {
      return -1;
    }
    ts->bit_count = 0;
  }

  int bit = (ts->buffer >> (7 - ts->bit_count)) & 1;
  ts->bit_count++;

  return bit;
}
void ts_read_multiple_bits(tree_serializer *ts, size_t bits, void *c) {
  *(size_t *)c = 0;

  unsigned char bit;
  for (int i = 0; i < bits; i++) {
    bit = ts_read_bit(ts);
    *(size_t *)c <<= 1;
    *(size_t *)c += bit;
  }
}

huffman_node_t *ts_deserialize_aux(tree_serializer *ts) {
  int bit = ts_read_bit(ts);

  if (bit == 0) {
    // Is an internal node
    huffman_node_t *left = ts_deserialize_aux(ts);
    huffman_node_t *right = ts_deserialize_aux(ts);
    return hn_init('\0', 0, left, right);
  }
  // Is a leaf
  char count;
  ts_read_multiple_bits(ts, ts->element_length, &count);

  wchar_t c;
  ts_read_multiple_bits(ts, (count + 1) * 8, &c);

  return hn_init(c, 0, NULL, NULL);
}

huffman_node_t *ts_deserialize(tree_serializer *ts) {
  ts->bit_count = 8; // Just to initialize reading first
  return ts_deserialize_aux(ts);
}

void ts_free(tree_serializer *ts) { free(ts); }
