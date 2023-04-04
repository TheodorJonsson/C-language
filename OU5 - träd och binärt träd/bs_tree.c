#include "bs_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

BSTree *bs_tree_make(int value)
{
  BSTree *root = malloc(sizeof(struct node));

  root->left_child = NULL;
  root->right_child = NULL;
  root->value = value;

  return root;
}

BSTreePos bs_tree_insert_left(int value, BSTreePos pos)
{
  return pos->left_child = bs_tree_make(value);
}

BSTreePos bs_tree_insert_right(int value, BSTreePos pos)
{
  return pos->right_child = bs_tree_make(value);
}

int bs_tree_inspect_label(BSTreePos pos)
{
  return pos->value;
}

bool bs_tree_has_left_child(BSTreePos pos)
{
  if(pos->left_child != NULL)
  {
    return true;
  }
  return false;
}

bool bs_tree_has_right_child(BSTreePos pos)
{
  if(pos->right_child != NULL)
  {
    return true;
  }
  return false;
}

BSTreePos bs_tree_root(BSTree *tree)
{
  BSTreePos root = tree;

  return root;
}

BSTreePos bs_tree_left_child(BSTreePos pos)
{
  return pos->left_child;
}

BSTreePos bs_tree_right_child(BSTreePos pos)
{
  return pos->right_child;
}

void bs_tree_destroy(BSTree *tree)
{
  if(tree == NULL)
  {
    return;
  }

  bs_tree_destroy(tree->left_child);
  bs_tree_destroy(tree->right_child);

  free(tree);
}
