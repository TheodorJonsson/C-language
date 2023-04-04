/**
 * @defgroup huffman.h huffman
 *
 * @brief
 * @version 0.1
 * @author Theodor Jonsson (ens18trn@cs.umu.se)
 * @date 2022-02-09
 *
 *
 *
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "frequence.h"
#include "huffman_trie.h"

#ifndef HUFFMAN_H
#define HUFFMAN_H

/**
 * @brief Prints the amount of bytes in the text file
 *
 * @param argc
 * @param argv
 */
void print_amount_bytes_before(int argc, char *argv[]);

void print_and_empty(pqueue *pq);
#endif
