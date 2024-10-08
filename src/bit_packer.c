#include "../include/bit_packer.h"
#include <stdint.h>

struct bit_packer {
  char buffer;
  unsigned int bit_pos;
  FILE *fp;
};

static inline unsigned int get_bit_length(size_t x) {
  return (x == 0) ? 0 : (sizeof(size_t) * 8 - __builtin_clzl(x));
}

bit_packer *bp_init(FILE *fp) {
  bit_packer *bp = (bit_packer *)malloc(sizeof(bit_packer));

  if (!bp)
    return NULL;

  bp->buffer = bp->bit_pos = 0;
  bp->fp = fp;
  return bp;
}

void bp_pack(bit_packer *bp, size_t val) {
  int length = get_bit_length(val) - 1;
  val &= (1UL << length) - 1;
  int bits_to_pack;
  while (length > 0) {
    int available_bits = 8 - bp->bit_pos;

    bits_to_pack = (length < available_bits) ? length : available_bits;

    // Shift the relevant part of the code into the correct position in the
    // buffer
    bp->buffer |= (val >> (length - bits_to_pack))
                  << (available_bits - bits_to_pack);

    bp->bit_pos += bits_to_pack;
    length -= bits_to_pack;

    if (bp->bit_pos == 8) {
      fwrite(&bp->buffer, sizeof(bp->buffer), 1, bp->fp);
      bp->buffer = bp->bit_pos = 0;
    }
  }
}

void bp_flush(bit_packer *bp) {
  if (bp->bit_pos > 0) {
    fwrite(&bp->buffer, sizeof(bp->buffer), 1, bp->fp);
  }
  bp->bit_pos = 0;
  bp->buffer = 0;
}

void bp_free(bit_packer *bp) { free(bp); }
