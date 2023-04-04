/**
 * @file frequence.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "huffman_trie.h"




/*--------Internal Functions----------*/
bool isLeaf(struct trie_node *root);
void print_binary_array(int arr[], int n);

void print_binary_array(int arr[], int n)
{
  for(int i = 0; i < n; i++)
  {
    printf("%d", arr[i]);
  }
  printf("\n");
}

int lessthantrie(void *elem1, void *elem2)
{
    return ((queue_elem *)elem1)->freq - ((queue_elem *)elem2)->freq;
}

bool isLeaf(struct trie_node *root)
{
  if(root->data != '$')
  {
    return true;
  }
  return false;
}
/*--------------------------------------*/
struct trie_node *new_node(char data, int freq)
{
  struct trie_node *new = malloc(sizeof(struct trie_node));

  new->freq = freq;
  new->data = data;

  return new;
}


struct trie_node *create_huffman(pqueue *pq)
{
  //struct trie_node *left, *right, *parent, *tree;
  queue_elem *q_elem1, *q_elem2;
  //pqueue *second = pqueue_empty(lessthantrie);

  while(!pqueue_is_empty(pq))
  {
    struct trie_node *temp = new_node('$',0);
    q_elem1 = (queue_elem *)pqueue_inspect_first(pq);
    pqueue_delete_first(pq);

    temp->left_child = new_node(q_elem1->character, q_elem1->freq);
    temp->freq = temp->left_child->freq;


    if(!pqueue_is_empty(pq))
    {
      q_elem2 = (queue_elem *)pqueue_inspect_first(pq);
      temp->right_child = new_node(q_elem2->character, q_elem2->freq);
      pqueue_delete_first(pq);

      temp->freq += temp->right_child->freq;
      //printf("%d\n", temp->freq);
      pqueue_insert(pq, temp);
    }
    else
    {
      return temp;
    }
  }

  return 0;
}

void print_binary_codes(struct trie_node *root, int arr[], int n)
{
  if(root->left_child)
  {
    arr[n] = 0;
    print_binary_codes(root->left_child, arr, n + 1);
  }
  if(root->right_child)
  {
    arr[n] = 1;
    print_binary_codes(root->right_child, arr, n + 1);
  }
  if(isLeaf(root) == true)
  {
    printf("%c: ", root->data);
    print_binary_array(arr, n);
  }

}
