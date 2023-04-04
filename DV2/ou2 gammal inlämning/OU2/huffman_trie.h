/**
* @file trie.h
* @author Theodor Jonsson (ens18trn@cs.umu.se)
* @brief
* @version 0.1
* @date 2022-02-11
*
* @copyright Copyright (c) 2022
*
*/
#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stdio.h>
#include "frequence.h"
#include "stdlib.h"




/**
* @define structure for the nodes in the trie
*
*/
struct trie_node
{
  int freq;
  char data;
  struct trie_node *left_child;
  struct trie_node *right_child;
};

typedef struct trie_node trie;

struct trie_node *new_node(char data, int freq);

struct trie_node *create_huffman(pqueue *pq);

void print_binary_codes(struct trie_node *root, int arr[], int n);


 #endif
