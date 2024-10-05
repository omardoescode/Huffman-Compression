#ifndef BIT_PACKER_HEADER
#define BIT_PACKER_HEADER
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bit_packer bit_packer;
struct bit_packer;

/**
 * @brief Construct a bit packer
 *
 * Initalize the buffer and bit position to zero. Set the file pointer to the
 * file argument
 *
 * @param out The file to pack the bytes to.
 * @return A pointer to the bit packer
 */
bit_packer *bp_init(FILE *out);

/**
 * @brief Pack the code into the buffer
 *
 * Packing means pushing the code into the buffer, ignoring all unused leftmost
 * zeros.
 * Codes are prefixed with leftmost 1 that needs to be removed
 * If the buffer is full, write the value to the file pointer
 *
 * @param bp A pointer to the bit packer
 * @param The code to pack
 */
void bp_pack(bit_packer *bp, size_t code);

/**
 * @brief Flush the buffer of the bit packer
 *
 * The flushed data must be shifted most left depending on the current bit
 * position
 *
 * @param bp A pointer to the bit packer
 */
void bp_flush(bit_packer *bp);

/**
 * @brief Free the bit packer
 *
 * The file isn't closed by this function and must be closed after using the bit
 * packer
 *
 * @param A pointer to the bit packer
 */
void bp_free(bit_packer *bp);

#endif // !BIT_PACKER_HEADER
