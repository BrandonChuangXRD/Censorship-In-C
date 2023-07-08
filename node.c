#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

Node *node_create(char *oldspeak, char *newspeak) {
  // TODO you probably need to use strncpy()
  Node *N = (Node *)calloc(1, sizeof(Node));
  N->oldspeak = strdup(oldspeak);
  if (newspeak != NULL) {
    N->newspeak = strdup(newspeak);
  }
  N->left = NULL;
  N->right = NULL;
  return N;
}

void node_delete(Node **n) {
  free(*n);
  *n = NULL;
  return;
}

void node_print(Node *n) {
  // this is not just for debugging, this is important.
  if (n->newspeak != NULL) {
    printf("%s -> %s\n", n->oldspeak, n->newspeak);
  } else {
    printf("%s\n", n->oldspeak);
  }
  return;
}
