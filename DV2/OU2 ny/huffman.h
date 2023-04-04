/**
* @defgroup huffman.h Huffman
*
* @brief Encodes and decodes files using huffman coding
*
* Lets the user choose from the command line to either
* encode a text file to a binary file or decode a binary
* file to a text file.
*
* If user chooses encoding the program will print
* amount of bytes used before encoding and
* the amount of bytes used after encoding.
*
* @author Theodor Jonsson (ens18trn@cs.umu.se)
* @version 0.1
* @since 2022-02-11
*
* @{
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frequence.h"
#include "huffman_trie.h"
#include "huffman_table.h"
#ifndef HUFFMAN_H
#define HUFFMAN_H


/**
* @brief Encodes the file
*
* Encodes the text file into a binary file using
* the huffman table to write the right huffman codes
*
* @param argc, amount of arguments from command line.
* @param argv[], arguments from command line.
*/
void encode(int argc, char *argv[]);

/**
* @brief Decodes the file
*
* Decodes the binary file into a text file
* using the huffman trie.
*
* @param argc, amount of arguments from command line.
* @param argv[], arguments from command line.
*/
void decode(int argc, char *argv[]);

/**
 * @brief Prints the amount of bytes in the text file
 *
 * Calculates the amount of bytes used in the text file
 * before encoding.
 *
 * @param argc
 * @param argv
 *
 * @return -
 */
void print_amount_bytes_before(int argc, char *argv[]);

/**
 * @brief Prints the amount of bytes in the binary file
 *
 * Calculates and prints the amount of bytes used after
 * encoding
 *
 * @param argc
 * @param argv
 *
 * @return -
 */
void print_amount_bytes_after(int argc, char *argv[]);

/**
* @brief writes the binary codes to a new file.
*
* Goes through the text file one character at a time
* and writes the corresponding huffman code to the binary file.
*
* @param hufftab, which is the huffman table.
* @param argc, number of command line argument.
* @param argv, command line argument.
* @param file_1, the file to read from.
* @param file_2, the file to write to.
*
* @return -
*/
void print_binary_codes_to_file(Huffman_table *hufftab, int argc, char *argv[],
                                                   FILE *file_1, FILE *file_2);

/**
* @}
*/

#endif
