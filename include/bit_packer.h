#ifndef BIT_PACKER_HEADER
#define BIT_PACKER_HEADER
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bit_packer bit_packer;
struct bit_packer;

bit_packer *bp_init(FILE *out);
void bp_pack(bit_packer *, size_t);
void bp_flush(bit_packer *);
void bp_free(bit_packer *);

#endif // !BIT_PACKER_HEADER
