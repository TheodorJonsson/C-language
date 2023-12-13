/**
* @defgroup mdu.h mdu
*
* @brief mdu the main algorithms for calculating files/directory sizes
*
* Contains the main algorithms used in calculating files/directories
* lets the user send in files or directory as arguments then
* calculates the size of these in 512b blocks
*
* @author Theodor Jonsson (ens18trn.cs.umu.se)
* @since 2022-10-08
* @{
*/
#ifndef MDU_H
#define MDU_H

#include <dirent.h>
#include "util.h"




/**
 * @brief The main algorithm for the pthreads
 * 
 * First it will lock using the mutex
 * Checks if the queue is empty and if it is the program
 * will wait using the conditional variable.
 * 
 * If isn't empty it will pick out the first task from the queue
 * then unlock the mutex letting other threads pick a task.
 * It will then check if it's a file or a directory, if the task is a file 
 * the function will send it away to be summed up, if the task is a 
 * directory it will send it away to be checked through for more tasks.
 * 
 * @param args, to contain the TaskQueue struct
 */
void *startThread(void *args);


/**
 * @brief Calculates the size of a file and sums it up to the right directory.
 * 
 * Uses the function count_file to get the size of 
 * the file then adds this sum to the directory sum from the param
 * 
 * @param task, the task to be calculated
 * @param dir, the directory to the sum is to be added
 * @param taskPool, used for locking the mutex
*/
void executeTask(struct task *task, Directory *dir, TaskQueue *taskPool);


/**
 * @brief The algorithm used for adding new directories.
 * 
 * Opens the directory and goes through each entry and checks if it's 
 * file or directory. 
 * If the entry is a file create it as a task and send it away to be calculated
 * if the entry is a directory create it as a task and enqueue it to the task queue
 * 
 * if the directory can't be opened sum up the size of taskDir from param.
 * 
 * @param taskPool, the struct used by the threads
 * @param taskDir, the task that was found to be a directory
*/
void submitDirectory(TaskQueue *taskPool, struct task *taskDir);


/**
 * @brief Concatenates the a string to a file path
 * 
 * Concatenates a string to make it 
 * to the format of: taskDir_name/file_name 
 * 
 * @param taskDir_name, the directorys name
 * @param file_name
*/
char *concat_dir_file(char *taskDir_name, char *file_name);


long int count_file(char *file_name);

/**
 * @brief Checks if a file is a directory or a file
 * g
 * @param mode, The st_mode from the lstat
 * 
 * @return true if it's a file, false if it's a directory, NULL if neither
 */
int check_if_file_or_dir(char *file_name);




#endif