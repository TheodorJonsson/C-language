/**
* @defgroup huffman_table.h Huffman table
*
* @brief A datatype representing a table of characters and their huffman code
*
* The huffman table can hold characters and their respective huffman code.
* This can be achieved using the huffman trie and traversering
* the trie to each leaf node and assign the character and insert the
* path to the bit buffer.
*
* User can search through the table with and integer as key to find
* the corresponding int in the table and its huffman code.
*
* @author Theodor Jonsson (ens18trn@cs.umu.se)
* @version 0.1
* @since 2022-02-11
*
* @{
*/
#ifndef HUFFMAN_TABLE_H
#define HUFFMAN_TABLE_H

#include <stdbool.h>
#include <stdio.h>
#include "huffman_trie.h"
#include "stdlib.h"
#include "bit_buffer.h"
/**
* @brief a structure to hold a character with corresponding binary code
*
* @elem data, an integer to hold the character
* @elem byte_code a bit_buffer to hold the binary code to the character.
*/
typedef struct huffman_table
{
  int data;
  bit_buffer *byte_code;
}Huffman_table;
/**
* @brief Gets the binary codes and puts them into a huffman table
*
* Goes through the entire trie and assigns each character and binary code
* to a huffmantable.
*
* @param root, which is the trie
* @param arr, which is the array to assign 0 or 1
* @param bitbuffer, which is the bit buffer to store the bits of each character
* @param hufftab, the huffman table to store all the values.
*
* @return -
*/
void get_binary_codes(struct trie_node *root, bit_buffer *bitbuffer,
                                             Huffman_table *hufftab);

/**
* @brief prints the huffman table
*
* Goes through the huffman table and prints the character
* with the corresponding binary code
*
* @param hufftab, which is the huffman table
*
* @return -
*/
void print_huffman_table(Huffman_table *hufftab);

/**
* @brief searches for the right character in the huffman table
*
* Searches through the huffman table array to find the position of
* the character from input. then returns that position.
*
*
* @param hufftab, which is the huffman table
* @param input, which is the value from file
*
* @return i, which is the position in the array the character is
*/
int search_value_in_huffman_table(Huffman_table *hufftab, int input);

/**
* @brief Deallocates the huffman table.
*
*
* @param hufftab, the huffman table.
*/
void destroy_huffman_table(Huffman_table *hufftab);
/**
 * @}
 */
#endif
