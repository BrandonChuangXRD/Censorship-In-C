#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitVector BitVector;

// taken from asgn 7 pdf
struct BitVector {
  uint32_t length;
  uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
  BitVector *bv = (BitVector *)malloc(sizeof(BitVector));
  if (bv) {
    bv->length = length;
    bv->vector = (uint8_t *)calloc((length + 7) / 8, sizeof(uint8_t));
    if (!bv->vector) {
      free(bv);
      bv = NULL;
    }
  }
  return bv;
}

void bv_delete(BitVector **bv) {
  if (*bv && (*bv)->vector) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
  }
  return;
}

uint32_t bv_length(BitVector *bv) { return bv->length; }

bool bv_set_bit(BitVector *bv, uint32_t i) {
  if (i > bv_length(bv)) {
    return false;
  }
  uint32_t byte = i / 8;      // position for vector[x]
  uint8_t bit_remain = i % 8; // position inside vector[x]'s uint8_t
  bv->vector[byte] = bv->vector[byte] | 1 << bit_remain;
  return true;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
  // this is the same as set but setting it to 0
  if (i > bv_length(bv)) {
    return false;
  }

  uint32_t byte = i / 8;      // position for vector[x]
  uint8_t bit_remain = i % 8; // position inside vector[x]'s uint8_t
  bv->vector[byte] = bv->vector[byte] & ~(1 << bit_remain);
  return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
  // check if i is out of bounds
  if (i > bv_length(bv)) {
    return false;
  }
  uint32_t byte = i / 8;
  uint8_t bit_remain = i % 8;
  return (bv->vector[byte] >> bit_remain) & 1;
}

void bv_print(BitVector *bv) {
  printf("length: %u\n", bv->length);
  for (uint32_t i = 0; i < bv->length; i++) {
    for (uint32_t j = 0; j < 8; j++) {
      printf("%u", (i >> j) & 1);
    }
    printf(" ");
  }
  printf("\n");
  return;
}
