#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ht.h"
#include "node.h"
#include "salts.h"
#include "speck.h"

uint64_t lookups = 0;

typedef struct HashTable HashTable;

// taken from asgn7 pdf
struct HashTable {
  uint64_t salt[2];
  uint32_t size;
  Node **trees;
};

HashTable *ht_create(uint32_t size) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    ht->size = size;
  }
  ht->trees = (Node **)calloc(size, sizeof(Node *));
  if (!ht->trees) {
    free(ht);
    ht = NULL;
  } else {
    for (uint32_t i = 0; i < size; i++) {
      ht->trees[i] = bst_create();
    }
  }
  return ht;
}

void ht_delete(HashTable **ht) {
  if (*ht && (*ht)->trees) {
    // delete the bst's
    for (uint32_t i = 0; i < (*ht)->size; i++) {
      bst_delete(&(*ht)->trees[i]);
    }
    free(*ht);
    *ht = NULL;
  }
  return;
}

uint32_t ht_size(HashTable *ht) { return ht->size; }

Node *ht_lookup(HashTable *ht, char *oldspeak) {
  // find the node with the given oldspeak or return null
  lookups += 1;
  if (!ht) {
    return NULL;
  }
  // find which bst to look through
  uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
  // look through that bst
  return bst_find(ht->trees[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
  lookups += 1;
  if (!ht) {
    return;
  }
  // find the right bst (index) to insert it
  uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
  // insert it
  ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
  return;
}

uint32_t ht_count(HashTable *ht) {
  // count the number of binary trees that aren't null
  uint32_t count = 0;
  for (uint32_t i = 0; i < ht->size; i++) {
    if (ht->trees[i] != NULL) {
      count++;
    }
  }
  return count;
}

double ht_avg_bst_size(HashTable *ht) {
  // count all nodes in all bst's
  uint32_t count = 0;
  uint32_t tree_count = 0;
  for (uint32_t i = 0; i < ht->size; i++) {
    if (ht->trees[i]) {
      count += bst_size(ht->trees[i]);
      tree_count += 1;
    }
  }
  return count / (double)tree_count;
}

double ht_avg_bst_height(HashTable *ht) {
  // count all the heights in all bst's
  uint32_t num_node = 0;
  uint32_t num_trees = 0;
  for (uint32_t i = 0; i < ht->size; i++) {
    if (ht->trees[i]) {
      num_node += bst_height(ht->trees[i]);
      if (ht->trees[i] != NULL) {
        num_trees++;
      }
    }
  }
  return num_node / (double)num_trees;
}

void ht_print(HashTable *ht);
