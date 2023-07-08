#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

uint64_t branches = 0;

Node *bst_create(void) { return NULL; }

uint32_t max_length = 0;
uint32_t curr_length = 0;
void bst_height_recursion(Node *curr_node) {
  if (curr_node == NULL) {
    return;
  }
  curr_length += 1;
  if (curr_length > max_length) {
    max_length = curr_length;
  }
  if (curr_node->left != NULL) {
    bst_height_recursion(curr_node->left);
  }
  if (curr_node->right != NULL) {
    bst_height_recursion(curr_node->right);
  }
  curr_length -= 1;
  return;
}

uint32_t bst_height(Node *root) {
  max_length = 0;
  curr_length = 0;
  bst_height_recursion(root);
  return max_length;
}

void bst_size_recursion(Node *curr_node, uint32_t *size) {
  if (curr_node == NULL) {
    return;
  }
  *size += 1;
  if (curr_node->left != NULL) {
    bst_size_recursion(curr_node->left, size);
  }
  if (curr_node->right != NULL) {
    bst_size_recursion(curr_node->right, size);
  }
  return;
}

uint32_t bst_size(Node *root) {
  uint32_t size = 0;
  bst_size_recursion(root, &size);
  return size;
}

Node *bst_find_recursion(Node *root, char *oldspeak) {
  if (root == NULL) {
    return NULL;
  }
  int cmp = strcmp(oldspeak, root->oldspeak);
  // set found_node to root if the oldspeaks equal
  if (cmp == 0) {
    return root;
  }
  // if the word were searching for is less than and left isnt NULL, continue
  // left down the tree
  else if (cmp < 0 && root->left != NULL) {
    branches += 1;
    return bst_find_recursion(root->left, oldspeak);
  }
  // if the word were searching for is greater than and right isnt NULL,
  // continue right down the tree
  else if (cmp > 0 && root->right != NULL) {
    branches += 1;
    return bst_find_recursion(root->right, oldspeak);
  }
  return NULL;
}

Node *bst_find(Node *root, char *oldspeak) {
  return bst_find_recursion(root, oldspeak);
}

void bst_insert_recursion(Node *curr_node, char *oldspeak, char *newspeak) {
  if (curr_node == NULL) {
    return;
  }
  int cmp = strcmp(oldspeak, curr_node->oldspeak);
  if (cmp > 0) { // if what were inserting is greater than
    if (curr_node->right !=
        NULL) { // continue recursing right if curr_node isnt a leaf
      branches += 1;
      bst_insert_recursion(curr_node->right, oldspeak, newspeak);
    } else {
      // make the node
      Node *r = node_create(oldspeak, newspeak);
      curr_node->right = r;
      branches += 1;
      return;
    }
  }
  if (cmp == 0) { // if they are equal (meaning its a duplicate)
    return;
  }
  if (cmp < 0) { // if what were inserting is less than curr_node
    if (curr_node->left !=
        NULL) { // continue recursing left if curr_node isnt a leaf
      branches += 1;
      bst_insert_recursion(curr_node->left, oldspeak, newspeak);
    } else {
      // make the node
      Node *l = node_create(oldspeak, newspeak);
      curr_node->left = l;
      branches += 1;
      return;
    }
  }
  return;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
  // returns root of tree after insert (according to Eugene)
  if (root == NULL) {                       // if the tree is empty
    root = node_create(oldspeak, newspeak); // create the tree
    return root;
  }
  // if tree is not empty
  bst_insert_recursion(root, oldspeak, newspeak);
  return root;
}

void bst_print(Node *root) {
  if (root == NULL) {
    return;
  }
  // recurse through the tree and print each node
  if (root->left != NULL) {
    bst_print(root->left);
  }
  if (root->right != NULL) {
    bst_print(root->right);
  }
  node_print(root);
  return;
}

void bst_delete(Node **root) {
  // recurse through the tree and delete starting from the bottom
  if (*root && (*root)->left != NULL) {
    bst_delete(&(*root)->left);
  }
  if (*root && (*root)->right != NULL) {
    bst_delete(&(*root)->right);
  }
  node_delete(root);
  *root = NULL;
}
