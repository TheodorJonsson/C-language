/**
 * @file huffman_table.c
 * @author Theodor Jonsson (thedders2@hotmail.com, ens18trn@cs.umu.se)
 * @brief
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "huffman_table.h"


void get_binary_codes(struct trie_node *root, bit_buffer *bitbuffer, Huffman_table *hufftab)
{
  bit_buffer *bit_buff;
  if(root == NULL)
  {
    return;
  }

  if(root->left_child == NULL && root->right_child == NULL)
  {
    hufftab[root->data].data = root->data;
    hufftab[root->data].byte_code = bit_buffer_copy(bitbuffer);
    return;
  }
  if(root->left_child != NULL)
  {
    bit_buff = bit_buffer_copy(bitbuffer);
    bit_buffer_insert_bit(bit_buff, 0);
    get_binary_codes(root->left_child, bit_buff, hufftab);

    bit_buffer_free(bit_buff);
  }

  if(root->right_child != NULL)
  {
    bit_buff = bit_buffer_copy(bitbuffer);
    bit_buffer_insert_bit(bit_buff, 1);
    get_binary_codes(root->right_child, bit_buff, hufftab);

    bit_buffer_free(bit_buff);
  }

}

void print_huffman_table(Huffman_table *hufftab)
{
  for(int i = 0; i < 256; i++)
  {
    printf("%c ", hufftab[i].data);
    for(int j = 0; j <= bit_buffer_size(hufftab[i].byte_code); j++)
    {
      printf("%d", bit_buffer_inspect_bit(hufftab[i].byte_code, j));
    }
    printf("\n");
  }
}

int search_value_in_huffman_table(Huffman_table *hufftab, int input)
{
  int i = 0;
  if(hufftab[i].data != input)
  {
    do
    {
      i++;
    } while(hufftab[i].data != input);
  }
  return i;
}

void destroy_huffman_table(Huffman_table *hufftab)
{
  for(int i = 0; i < 255; i++)
  {
    bit_buffer_free(hufftab[i].byte_code);
  }
  free(hufftab);
}
