
/**
* @defgroup frequence.h Frequence
*
* @brief Analyzes and stores the frequency of characters in a text file
*
* Goes through the text file character per character and counts the frequency
* of each character. Then inserts these values in to a priority queue with
* the weighting coming from the frequency of the characters.
* 
* @author Theodor Jonsson (ens18trn@cs.umu.se)
* @version 0.1
* @since 2022-02-11
*
* @{
*/

#ifndef FREQUENCE_H
#define FREQUENCE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#include <string.h>


/**
 * @brief a structure to hold the frequency of each character.
 *
 * @elem freq, which is the frequency of the character.
 * @elem character, which is the character.
 */
typedef struct
{
    int freq;
    int character;
} queue_elem;

/**
* @brief Creates a priority queue with the characters and their frequency
*
* Goes through the entire text and counts the frequency of each character
* then places these values in to a priority queue where the weighting
* is determined from the frequency of the characters.
*
* @param argc, amount of arguments from command line
* @param argv, arguments from command line
* @param in , the input file to analyze
*
* @return
*/
pqueue *analyze_frequency(int argc, char *argv[], FILE *in);


/**
 * @brief Creates and returns a int array
 *
 * Creates and populates int array from 0-255 to represent every ASCII character.
 *
 * @return character
 */
int *populate_int_array(void);

/**
 * @brief Creates and returns a array with zeroes
 *
 * creates a int array from 0-255 and assign 0 to all of them
 *
 * @return freq
 */
int* zero_array(void);

/**
* @}
*/


#endif
