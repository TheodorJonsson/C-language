
/**
 * @file frequence.h
 * @author Theodor Jonsson (ens18trn@cs.umu.se)
 * @brief
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef FREQUENCE_H
#define FREQUENCE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#include <string.h>

/**
 * @brief
 *
 */
typedef struct
{
    int freq;
    char character;
    
} queue_elem;

/**
 * @brief Analyses and creates priorityqueue of the values in the text
 *
 * @param in , the input file to analyze
 * @return
 */
pqueue *analyze_frequency(int argc, char *argv[], FILE *in);


/**
 * @brief Creates and returns a char with every character
 *
 * User is responsible of deallocating memory for array
 *
 * @return character
 */
char* populate_char_array(void);

/**
 * @brief Creates and returns a array with zeroes
 *
 * User is responsible of deallocating memory for array
 *
 * @return freq
 */
int* zero_array(void);

/**
 * @brief Get the frequency object
 *
 * @param character
 * @param freq
 * @param in
 * @param argc
 * @param argv
 * @return return 0 if unsuccesful in opening file. return 1 if succesful
 */
int get_frequency(char *character, int *freq, FILE *in, int argc, char *argv[]);


#endif
