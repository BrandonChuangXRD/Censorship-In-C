#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bf.h"
#include "bv.h"
#include "salts.h"
#include "speck.h"

typedef struct BloomFilter BloomFilter;

// copied from assignment 7 pdf (Credit: Darrell Long)
struct BloomFilter {
  uint64_t primary[2];
  uint64_t secondary[2];
  uint64_t tertiary[2];
  BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;
  }
  // basically identical to stack_create's item creation(Credit: Darrell Long)
  bf->filter = (BitVector *)calloc(size, sizeof(BitVector *));
  if (!bf->filter) {
    free(bf);
    bf = NULL;
  } else {
    bf->filter = bv_create(size);
  }
  return bf;
}

void bf_delete(BloomFilter **bf) {
  if (*bf && (*bf)->filter) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
  }
  return;
}

uint32_t bf_size(BloomFilter *bf) { return bv_length(bf->filter); }

void bf_insert(BloomFilter *bf, char *oldspeak) {
  // hash with each the 3 indicies
  // set the bits at the bit vector
  uint32_t hashed_primary = hash(bf->primary, oldspeak) % bf_size(bf);
  uint32_t hashed_secondary = hash(bf->secondary, oldspeak) % bf_size(bf);
  uint32_t hashed_tertiary = hash(bf->tertiary, oldspeak) % bf_size(bf);

  bv_set_bit(bf->filter, hashed_primary);
  bv_set_bit(bf->filter, hashed_secondary);
  bv_set_bit(bf->filter, hashed_tertiary);
  return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
  // get the 3 hash values and see if the bits are set in the filter
  uint32_t hashed_primary = hash(bf->primary, oldspeak) % bf_size(bf);
  uint32_t hashed_secondary = hash(bf->secondary, oldspeak) % bf_size(bf);
  uint32_t hashed_tertiary = hash(bf->tertiary, oldspeak) % bf_size(bf);

  if (bv_get_bit(bf->filter, hashed_primary) &&
      bv_get_bit(bf->filter, hashed_secondary) &&
      bv_get_bit(bf->filter, hashed_tertiary)) {
    return true;
  }
  return false;
}

uint32_t bf_count(BloomFilter *bf) {
  uint32_t count = 0;
  for (uint32_t i = 0; i < bf_size(bf) * 8; i++) {
    if (bv_get_bit(bf->filter, i)) {
      count++;
    }
  }
  return count;
}

void bf_print(BloomFilter *bf);
