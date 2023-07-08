#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bf.h"
#include "bst.h"
#include "bv.h"
#include "helpprints.h"
#include "ht.h"
#include "messages.h"
#include "node.h"
#include "parser.h"

#define OPTIONS "ht:f:s"
#define T_SIZE_DEFAULT 65536
#define F_SIZE_DEFAULT 1048576
#define WORD "([a-zA-Z0-9_]+-*'*)+"
int main(int argc, char **argv) {
  // parse through inputs
  int opt = 0;

  uint64_t t = T_SIZE_DEFAULT;
  uint64_t f = F_SIZE_DEFAULT;
  bool print_stats = false;

  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
    switch (opt) {
    case 'h':
      helpprints();
      break;
    case 't':
      t = atoi(optarg);
      break;
    case 'f':
      f = atoi(optarg);
      break;
    case 's':
      print_stats = true;
      break;
    }
  }

  // initialize hash table and bloom filter
  HashTable *potato = ht_create(t);
  BloomFilter *rose = bf_create(f);
  // read badspeak with fscanf() and add it to bloom filter and hash table
  char temp_bad[256];
  FILE *badspeak;
  badspeak = fopen("badspeak.txt", "r");
  while (fscanf(badspeak, "%s\n", temp_bad) != EOF) {
    bf_insert(rose, temp_bad);
    ht_insert(potato, temp_bad, NULL);
  }
  fclose(badspeak);

  // read newspeak with fscanf() and add it to both the hashtable and the bloom
  // filter
  char temp_new[256];
  FILE *newspeak;
  newspeak = fopen("newspeak.txt", "r");

  while (fscanf(newspeak, "%s %s\n", temp_bad, temp_new) != EOF) {
    ht_insert(potato, temp_bad, temp_new);
    bf_insert(rose, temp_bad);
  }

  // close the files
  fclose(newspeak);

  // read words from stdin using the parsing module
  regex_t re;
  if (regcomp(&re, WORD, REG_EXTENDED)) {
    printf("Failed to compile regex.\n");
    return 1;
  }

  char *word;

  // check the words in the bloom filter using bf_probe, then the hash table if
  // true
  bool bad = false;
  bool good = false;

  // use two bst's of nodes
  Node *goodies = bst_create();
  Node *baddies = bst_create();

  while ((word = next_word(stdin, &re)) != NULL) {
    for (uint32_t i = 0; i < strlen(word); i++) {
      word[i] = (char)tolower((int)word[i]);
    }
    // now instead of printing the word, check the word
    if (bf_probe(rose, word)) {
      Node *naughty = ht_lookup(potato, word);
      if (naughty != NULL) {
        if (naughty->newspeak == NULL) {
          // badspeak
          // iterate through the array of nodes and add it if it isnt already
          // there
          bad = true;
          baddies = bst_insert(baddies, naughty->oldspeak, NULL);
        } else {
          // goodspeak
          ////iterate through the array of nodes and add it if it isnt already
          ///there
          good = true;
          goodies = bst_insert(goodies, naughty->oldspeak, naughty->newspeak);
        }
      }
    }
  }

  // print stuff out
  if (!print_stats) {
    if (bad && good) {
      printf("%s", mixspeak_message);
    } else if (bad) {
      printf("%s", badspeak_message);
    } else if (good) {
      printf("%s", goodspeak_message);
    }
    bst_print(baddies);
    bst_print(goodies);
  } else {
    printf("Average BST size: %f\n", ht_avg_bst_size(potato));
    printf("Average BST height: %f\n", ht_avg_bst_height(potato));
    printf("Average branches traversed: %f\n", branches / (double)lookups);
    // calculate hash table load
    printf("Hash table load: %f%%\n",
           100 * (double)ht_count(potato) / (double)ht_size(potato));
    // calculate bloom filter load
    printf("Bloom filter load: %f%%\n",
           100 * (double)bf_count(rose) / (double)bf_size(rose));
  }

  ht_delete(&potato);
  bf_delete(&rose);

  return 0;
}
