/**
 * @defgroup mmake.h make
 * 
 * @brief Simple version of the UNIX tool Make
 * 
 * Reads a makefile the default file should be named mmakefile if a different file
 * is desired then use the flag -f and send the name of the file as arguments.
 * This program will build a executable file from the first string in the makefile
 * and all it's prerequisites or specified targets from the user. 
 * 
 * @author Theodor Jonsson (ens18trn@cs.umu.se)
 * @since 2022-09-27
 * @{
 */
#ifndef MMAKE_H
#define MMAKE_H

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <time.h>
#include "parser.h"

/**
 * @brief The structure that holds the flag conditions 
 * 
 * file_name will hold the name of file if flag_f is true
 */
struct flags{
    char *file_name;
    bool flag_s;
    bool flag_B;
    bool flag_f;
};


/**
 * @brief Gets the targets for the makefile
 * 
 * If there is any targets for the makefile 
 * it will store it in a array of strings
 * 
 * @param argc, the amount of arguments
 * @param argv, the array of arguments
 * 
 * @return cmd, which is the array of strings
 */
char **get_cmd(int argc, char *argv[]);

/**
 * @brief Initiates the struct flags
 * 
 * Reads the arguments and searches for the flags "f", "B" and "s"
 * will set the corresponding flags to true if it finds
 * the flag in the arguments.
 *  
 * @param argc, the amount of arguments
 * @param argv, the array of arguments
 * 
 * @return flag, which is the struct
 */
struct flags *check_flags(int argc, char *argv[]);

/**
 * @brief Goes through the makefile checking which targets should be built
 * 
 * First it checks if the target_names file exists and if there is rule to build it.
 * then recursively sends all the prerequisites to itself. 
 * The function will check if the file should be built 
 * if it should then it will be sent to exec_target.
 * 
 * @param make, the parsed makefile
 * @param target_name, the string containing the targets name
 * @param flag, the struct containing which flags are used
 */
void build_target(makefile *make, const char *target_name, struct flags *flag);

/**
 * @brief Checks if the target should be built
 * 
 * First checks if the flag "B" is true or not if it is true 
 * then returns true.
 * Then checks if the prerequisite file 
 * is newer than the target file
 * 
 * @param prereq_name, the string containing one of the names of the target
 * @param target_name, the string containing the targets name
 * 
 * @return TRUE if it should be built, FALSE if not.
 */
bool check_if_target_should_be_built(const char *prereq_name, const char *target_name, struct flags *flag);

/**
 * @brief Executes the commands from the rule
 * 
 * if the flag "s" is false then it will print out 
 * the commands that it will execute if it's true
 * then it won't print out anything.
 * 
 * @param rule, the commands to be used for exec
 * @param flag, the struct of flags
 */
void exec_target(rule *rule, struct flags *flag);

/**
 * @brief Deallocates memory
 * 
 * @param cmd, the array of strings containing targets
 * @param flag, the struct of flags
 * @param make, the parsed makefile
 */ 
void deallocation(char **cmd, struct flags *flag, makefile *make);

#endif 