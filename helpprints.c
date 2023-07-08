#include <stdio.h>

#include "helpprints.h"

void helpprints(void) {
  printf("SYNOPSIS\n");
  printf("  A word filtering program for the GPRSC.\n");
  printf("  Filters out and reports bad words parsed from stdin.\n");
  printf("\n");
  printf("USAGE\n");
  printf("  ./banhammer [-hs] [-t size] [-f size]\n");
  printf("\n");
  printf("OPTIONS\n");
  printf("  -h           Program usage and help.\n");
  printf("  -s           Print program statistics.\n");
  printf("  -t size      Specify hash table size (default: 2^16).\n");
  printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
  return;
}
