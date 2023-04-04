/**
 * @file huffman_table.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "huffman_trie.h"
#include "huffman_table.h"



/*--------Internal Functions----------*/

void print_binary_array(int *arr, int n)
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

pqueue *convert_to_trie_nodes(pqueue *pq)
{
  pqueue *new = pqueue_empty(lessthantrie);
  while(!pqueue_is_empty(pq))
  {
    struct trie_node *temp;
    queue_elem *q_elem = (queue_elem *)pqueue_inspect_first(pq);

    temp = new_node(q_elem->character, q_elem->freq);
    free(q_elem);
    pqueue_delete_first(pq);
    pqueue_insert(new, temp);

  }
  pqueue_kill(pq);
  return new;
}



int search_trie(struct trie_node *root, FILE *file_1, int argc, char *argv[])
{

  struct trie_node *current = root;
  int input;
  while(current != NULL)
  {
    input = getc(file_1);
    if(current->left_child == NULL && current->right_child == NULL)
    {
      return current->data;
    }
    if((char)input == '0')
    {
      current = current->left_child;
    }
    else if((char)input == '1')
    {
      current = current->right_child;
    }
  }
  return 0;
}
/*--------------------------------------*/
struct trie_node *new_node(int data, int freq)
{
  struct trie_node *new = malloc(sizeof(struct trie_node));

  new->freq = freq;
  new->data = data;
  new->right_child = NULL;
  new->left_child = NULL;
  return new;
}


struct trie_node *create_huffman_trie(pqueue *pq)
{
  pqueue *pq_new = convert_to_trie_nodes(pq);

  while(!pqueue_is_empty(pq_new))
  {
    struct trie_node *temp = new_node('$',0);
    temp->left_child = pqueue_inspect_first(pq_new);
    //printf("left %c\n", temp->left_child->data);
    pqueue_delete_first(pq_new);

    if(!pqueue_is_empty(pq_new))
    {
      temp->right_child = pqueue_inspect_first(pq_new);
      //printf("right %c\n", temp->right_child->data);
      pqueue_delete_first(pq_new);
      temp->freq = temp->right_child->freq + temp->left_child->freq;
      pqueue_insert(pq_new, temp);
    }
    else
    {
      pqueue_kill(pq_new);
      return temp->left_child;
    }
  }

  return 0;
}

void search_through_trie_and_print_to_file(struct trie_node *root, int argc, char *argv[], FILE *file_1, FILE *file_2)
{
  int found;

  file_2 = fopen(argv[4], "w");
  if(file_2 == NULL)
  {
    printf("Could not open the output file %s\n", argv[4]);
    fclose(file_2);
    return;
  }
  file_1 = fopen(argv[3], "r");
  if(file_1 == NULL)
  {
    printf("Could not open the input file %s\n", argv[3]);
    fclose(file_1);
    return;
  }
  do
  {
    struct trie_node *searchtrie = root;
    found = search_trie(searchtrie, file_1, argc , argv);
    //printf("%c", found);
    fprintf(file_2, "%c", found);
    //i++;
  } while(found != 4);

}


void destroy_trie(struct trie_node *root)
{
  if(root->left_child == NULL && root->right_child == NULL)
  {
    return;
  }
  destroy_trie(root->left_child);
  destroy_trie(root->right_child);
  free(root);

}

/*----------------External function used for debugging----------------*/
void print_binary_codes(struct trie_node *root, int *arr, int n)
{
  if(root == NULL)
  {
    return;
  }
  if(root->left_child == NULL && root->right_child)
  {
    printf("%c: ", root->data);
    print_binary_array(arr, n);
    return;
  }
  arr[n] = 0;
  print_binary_codes(root->left_child, arr, n + 1);
  arr[n] = 1;
  print_binary_codes(root->right_child, arr, n + 1);
}
