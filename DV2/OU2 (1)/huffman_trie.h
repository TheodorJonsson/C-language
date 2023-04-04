/**
* @defgroup huffman_trie.h Huffman trie
*
* @brief Creates a huffman trie and can search through it.
*
* Lets the create a huffman trie using the priority queue from the
* frequence analysis.
* If used for decoding uses the huffman trie to decode the binary file
* and prints to the text file.
*
* @author Theodor Jonsson (ens18trn@cs.umu.se)
* @version 0.1
* @since 2022-02-11
*
* @{
*/
#ifndef HUFFMAN_TRIE_H
#define HUFFMAN_TRIE_H

#include <stdbool.h>
#include <stdio.h>
#include "frequence.h"
#include "stdlib.h"
#include "bit_buffer.h"



/**
* @brief structure for the nodes in the trie
*
* @elem freq, the frequency of the character.
* @elem data, the character.
* @elem left_child, a pointer to a trie_node which is the left child
* @elem right_child, a pointer to a trie_node which is the right child
*/
struct trie_node
{
  int freq;
  int data;
  struct trie_node *left_child;
  struct trie_node *right_child;
};


/**
* @brief Creates a new node
*
* Allocates memory for the node.
* Assigns data and frequency to the node. Aswell as NULLs the
* pointers to the left and right child
*
* @param data, which is the character
* @param freq, which is the frequency of the character
*
* @return new, returns the newly created node
*/
struct trie_node *new_node(int data, int freq);

/**
* @brief Creates a new node
*
* Uses internal function to convert the nodes to trie nodes.
* Then creates a new trie node and assigns the two lowest frequency
* nodes as the new nodes left and right child
* then repeats this until the pqueue is empty and the tree is fully created
*
* @param pq, which is the pqueue
*
* @return temp_left->child when all the elements in the pqueue is empty
*         returns 0 if the pqueue is empty from the start
*/
struct trie_node *create_huffman_trie(pqueue *pq);

/**
* @brief Goes through the binary file and searches for the right character.
*
* Goes through the binary file one character at a time
* using these characters traverses the trie until it finds a leaf
* then prints the character in the leaf to the text file.
*
* @param root, which is the trie
* @param argc, amount of arguments from the command line
* @param argv, arguments from the command line
* @param file_1, which is the binary file
* @param file_2, which is the text file
*
* @return -
*/
void search_through_trie_and_print_to_file(struct trie_node *root, int argc, char *argv[], FILE *file_1, FILE *file_2);
/**
* @brief Deallocates the trie
*
* Goes through the trie and deallocates each leaf
* then deallocates each node.
*
* @return -
*/
void destroy_trie(struct trie_node *root);
/*----------------External function used for debugging----------------*/
/**
* @brief Prints the entire trie
*
* Goes through the entire trie and prints out all the binary codes for
* each character.
*
* @param root, which is the trie
* @param arr, is the array to write the binary codes in.
* @oaram n, to know where in the array to print either 0 or 1
*
* @return -
*/
void print_binary_codes(struct trie_node *root, int arr[], int n);
/**
* @}
*/
 #endif
