
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 100000
#define ARMS 6
#define MAXSIZEARM 10000000

struct node
{
    int orderofinsertion;
    int value;
    int *snowflakes;
    struct node *left_child;
    struct node *right_child;
};
typedef struct node BSTree;
typedef struct node* BSTreePos;

void fill_snowflakes(int snowflakes[SIZE][ARMS], int flakes);
bool is_equal(int snowflakes[SIZE][ARMS], int flakes, int value[SIZE], BSTree *root);
bool compare_snowflakes(int snowflake_1[], int *snowflake_2);

BSTree *bs_tree_make(int value, int *snowflakes, int orderofinsertion);

BSTreePos bs_tree_insert_left(int value, int *snowflakes, BSTreePos pos, int orderofinsertion);
BSTreePos bs_tree_insert_right(int value, int *snowflakes, BSTreePos pos, int orderofinsertion);

int bs_tree_inspect_label(BSTreePos pos);

bool bs_tree_has_left_child(BSTreePos pos);
bool bs_tree_has_right_child(BSTreePos pos);

BSTreePos bs_tree_root(BSTree *tree);
BSTreePos bs_tree_left_child(BSTreePos pos);
BSTreePos bs_tree_right_child(BSTreePos pos);

void bs_tree_destroy(BSTree *tree);

void insert_value(int value, int *snowflakes, BSTreePos pos, int orderofinsertion);
BSTreePos search_value(int value, BSTreePos pos, int orderofinsertion);

int main(void)
{
  int flakes = 0;
  static int snowflakes[SIZE][ARMS], value[SIZE];

  scanf("%d", &flakes);
  fill_snowflakes(snowflakes, flakes);

  for(int i = 0; i < flakes; i++)
  {
    for(int j = 0; j < 6; j++)
    {
        value[i] = value[i] + snowflakes[i][j];
    }
  }
  BSTree *root = bs_tree_make(value[0], snowflakes[0], 0);
  for(int i = 1; i < flakes; i++)
  {
    BSTreePos pos = bs_tree_root(root);
    insert_value(value[i], snowflakes[i], pos, i);
  }


  if(is_equal(snowflakes, flakes, value, root) == true)
  {
    printf("Twin snowflakes found.\n");
  }

  else
  {
    printf("No two snowflakes are alike.\n");
  }
  bs_tree_destroy(root);
  return 0;
}


void fill_snowflakes(int snowflakes[SIZE][ARMS], int flakes)
{
   int input;

   for(int i = 0; i < flakes; i++) {

      for(int j = 0; j < 6; j++) {

         scanf("%d", &input);
         if(input >= 0 && input < MAXSIZEARM)
         {
           snowflakes[i][j] = input;
         }
      }
   }
}
bool is_equal(int snowflakes[SIZE][ARMS], int flakes, int value[SIZE], BSTree *root)
{
  for(int i = 0; i < flakes; i++)
  {
    BSTreePos pos = bs_tree_root(root);
    BSTreePos found;
    if((found = search_value(value[i], pos, i)) != NULL)
    {
      if(compare_snowflakes(snowflakes[i], found->snowflakes) == true)
      {
        return true;
      }
    }
  }
  return false;
}


bool compare_snowflakes(int snowflake_1[], int snowflake_2[])
{
  int value = 0;

  for(int i = 0; i < 6; i++)
  {
    if(snowflake_1[0] == snowflake_2[i])
    {
      for(int j = 0; j < 6; j++)
      {
        if((snowflake_1[j] != snowflake_2[(j + value) % 6]) &&
          (snowflake_1[j] != snowflake_2[((value - j) + 6) % 6]) &&
          (snowflake_1[-j % 6] != snowflake_2[(j + value) % 6]) &&
          (snowflake_1[-j % 6] != snowflake_2[(value - j) % 6]))
        {
          return false;
        }
      }
      return true;
    }
    value++;
  }
  return false;
}
/////////////////////BINARY SEARCH TREE FUNCTIONS/////////////////////////////////////////
void insert_value(int value, int *snowflakes, BSTreePos pos, int orderofinsertion)
{
  BSTreePos current = pos;
  BSTreePos previous = NULL;

  while(current != NULL)
  {
    previous = current;
    if(value < bs_tree_inspect_label(current))
    {
      current = bs_tree_left_child(current);
    }
    else
    {
      current = bs_tree_right_child(current);
    }
  }

  if(value < bs_tree_inspect_label(previous))
  {
    bs_tree_insert_left(value, snowflakes, previous, orderofinsertion);
  }
  else
  {
    bs_tree_insert_right(value, snowflakes, previous, orderofinsertion);
  }
}

BSTreePos search_value(int value, BSTreePos pos, int orderofinsertion)
{
  BSTreePos current = pos;

  while(current != NULL)
  {
    if(value == bs_tree_inspect_label(current))
    {
      if(orderofinsertion != current->orderofinsertion)
      {
        return current;
      }
    }
    if(value < bs_tree_inspect_label(current))
    {
      current = bs_tree_left_child(current);
    }
    else
    {
      current = bs_tree_right_child(current);
    }
  }
  return NULL;
}

BSTree *bs_tree_make(int value, int *snowflakes, int orderofinsertion)
{
  BSTree *root = malloc(sizeof(struct node));

  root->left_child = NULL;
  root->right_child = NULL;
  root->value = value;
  root->snowflakes = snowflakes;
  root->orderofinsertion = orderofinsertion;

  return root;
}

BSTreePos bs_tree_insert_left(int value, int *snowflakes, BSTreePos pos, int orderofinsertion)
{
  return pos->left_child = bs_tree_make(value, snowflakes, orderofinsertion);
}

BSTreePos bs_tree_insert_right(int value, int *snowflakes, BSTreePos pos, int orderofinsertion)
{
  return pos->right_child = bs_tree_make(value, snowflakes, orderofinsertion);
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
