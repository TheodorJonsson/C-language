/**
 * @defgroup mexec.h mexec
 * 
 * @brief Uses Pipes and forks to parallel execute different programs
 * 
 * In this particular case it will execute cat then grep and lastly less
 * using the perceeding one as input for the next
 * 
 * @author Theodor Jonsson (ens18trn@cs.umu.se)
 * @since 2022-09-07
 * @{
 */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFF 1024

#ifndef MEXEC_H
#define MEXEC_H
/**
 * @brief Reads the input from either a file or stdin 
 * 
 * Allocates memory for a string to store the input
 * Then gets the input and stores it in the string
 * 
 * @param inputstream, which is the input
 * 
 * @return input_string, which is the string from the input
 */ 
char *read_input_string(FILE *inputstream);


/**
 * @brief Counts the amount of lines from the input string
 * 
 * Counts each occurence of counting_character from the parameter
 * in the string from the parameters
 * 
 * @param input_string, which is the string to be counted from
 * @param counting_character, which is the character to be used when counting
 * 
 * @return nr_of_strings, the amount of counting characters in the string
 */ 
int amount_of_strings(char *input_string, char counting_character);

/**
 * @brief Splits the input string into an array of strings
 * 
 * Uses strtok to split the input_string into an array of strings
 * Splits the string at the splitting_character
 * 
 * @param input_string, the string to be split
 * @param nr_of_strings, the amount of strings, used for allocating memory
 * @param splitting_character, the character to where the string is to be split
 * 
 * @return splitting_string,
 */
char **split_input_string(char *input_string, int nr_of_strings, char* splitting_character);

int **creating_pipes(int nr_of_strings);

/**
 * @brief Creating the desired amount of pipes
 * 
 * 
 * @param nr_of_pipes, the amount of pipes to be created
 * @param pipe_array, a 2d array used in creating pipes
 */
void create_pipes(int nr_of_pipes, int pipe_array[nr_of_pipes][2]);

/**
 * @brief Creates forks for executing
 * 
 * Uses a loop to create forks, one less then the amount of strings
 * For each child go in to the function connecting_pipes_and_exec
 * 
 * 
 * @param input_string, which is the string array used in the arguments for exec
 * @param nr_of_pipes, the amount of pipes
 * @param pipe_array, the array of pipes
 * @param nr_of_strings, the amount of strings
 * @param input_from_file, the input string (only used for deallocating incase of an error)
 * 
 * @return child, which is the pid of the last fork
 */
void creating_forks(char **input_string, int nr_of_pipes, int pipe_array[nr_of_pipes][2], int nr_of_strings, char *input_from_file);

/**
 * @brief Connects the pipes between the forks then executes the program
 * 
 * Connects the pipes between the children. If it's the first child
 * it will only dup the output. If it's one of the middle child/children
 * it will dup both input and output. Lastly if it's the last child it
 * will dup the input.
 * Then it will close all the pipes
 * Using the strings for the input_string it will execute a new program.
 * 
 * @param nr_of_child, the number of the current child
 * @param input_string, the string array which contains the arguments for exec
 * @param nr_of_pipes, the amount of pipes
 * @param pipe_array, the array of pipes
 * @param nr_of_strings, the amount of strings
 * @param input_from_file, the input string (only used for deallocating incase of an error)
 */
void connecting_pipes_and_exec(int nr_of_child, char **input_string, int nr_of_pipes, int pipe_array[nr_of_pipes][2], int nr_of_strings, char *input_from_file);

/**
 * @brief Deallocates the allocated memory
 * 
 * 
 * @param input_string, the string array
 * @param input_from_file, the input string
 * @param nr_of_strings, the amount of strings
 */
void deallocate_everything(char **input_string, char *input_from_file, int nr_of_strings);

/**
 * @}
 */
#endif  