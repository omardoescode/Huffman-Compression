#include "../include/bit_unpacker.h"

struct bit_unpacker {
  char buffer;
  unsigned int bit_pos;
  FILE *inp;
  huffman_node_t *tree;
  huffman_node_t *temp;
};

bit_unpacker *bu_init(huffman_node_t *tree, FILE *fp) {
  bit_unpacker *bu = (bit_unpacker *)malloc(sizeof(bit_unpacker));

  if (!bu)
    return NULL;

  bu->buffer = 0;
  bu->bit_pos = 8; // Assume it's full just to read the next one
  bu->inp = fp;
  bu->tree = bu->temp = tree;
  return bu;
}

char bu_get_bit(bit_unpacker *bu) {
  // load the next one if full
  if (bu->bit_pos == 8) {
    if (fread(&bu->buffer, 1, 1, bu->inp) != 1) {
      return -1;
    }
    bu->bit_pos = 0;
  }

  char bit = (bu->buffer >> (7 - bu->bit_pos)) & 1;
  bu->bit_pos++;
  return bit;
}

void bu_unpack(bit_unpacker *bu, FILE *out) {
  while (1) {
    char bit = bu_get_bit(bu);
    if (bit == -1)
      return;

    if (bit == 0) {
      bu->temp = bu->temp->left;
    } else if (bit == 1) {
      bu->temp = bu->temp->right;
    }

    if (hn_is_leaf(bu->temp)) {
      bu->temp = bu->tree;
    }
  }
}

void bu_free(bit_unpacker *bu) { free(bu); }
