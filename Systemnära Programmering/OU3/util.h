/**
* @defgroup util.h util
*
* @brief Contains the tasks and taskqueue and other functions used for mdu
*
* (DISCLAIMER) TaskQueue and taskList have misleading names TaskQueue is the main struct
* for all the threads while tasklist is the queue of tasks.
*
*
* @author Theodor Jonsson (ens18trn.cs.umu.se)
* @since 2022-10-08
* @{
*/
#ifndef UTIL_H
#define UTIL_H

#include <pthread.h>
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


/**
 * @brief struct for tasks
 * 
 * dirID, the id of its directory.
 * file_name, the path to the file.
 * next, the next task.
 * prev, the previous task.
*/
struct task{
    int dirID;
    char *file_name;
    struct task *next;
    struct task *prev;
};

/**
 * @brief struct for the taskList which is more of a queue
 * 
 * task_head, which is the head of the queue
*/
typedef struct tasklist{
    struct task *task_head;
}taskList;

/**
 * @brief struct for the initial arguments to keep track of what to print out
 * 
 * directoryName, the name of the argument
 * ID, an int corresponding to it's position in the array
 * sum, the sum of it's files
*/
typedef struct directory{
    char *directoryName;
    int ID;
    long int sum;
}Directory;


/**
 * @brief the main struct used by all threads
 * 
 * dir, a 2d array of directories
 * task_head, the head of the task queue
 * curr_task, only used in deallocation
 * amount_of_dir, how many directories there are
 * finished, variable to check if the threads should complete or not
 * success, if the threads completed the task without failures
 * mutexQue, mutex used for locking threads
 * condQue, conditional variable used for waiting the threads
*/
typedef struct taskQueue{
    Directory **dir;
    taskList *task_head;
    struct task *curr_task;
    int amount_of_dir;
    bool finished;
    int success;
    pthread_mutex_t mutexQue;
    pthread_cond_t condQue;
}TaskQueue;

/**
 * @brief Initiliazes the taskQueue
 * 
 * Allocates memory for a head of queue
 * and sets the prev task and next task to the head
 * 
 * @return list, which is actually a queue
*/
taskList *create_TaskList(void);

/**
 * @brief Creates a task
 * 
 * Allocates memory for the task
 * then sets its values using the values 
 * from the parameters
 * 
 * @param file_name, the path to the file
 * @param dirID, id to its directory
 * @return task
*/
struct task *create_Task(char *file_name, int dirID);

/**
 * @brief returns the first task in the queue
 * 
 * @param tsk_lst, the head of the queue
 * @return the first task
*/
struct task *first_Task(taskList *tsk_lst);

/**
 * @brief returns the next task in the queue
 * 
 * @param tsk_lst, the current task
 * @return the next task
*/
struct task *next_Task(struct task *tsk_lst);

/**
 * @brief returns the last task in the queue
 * 
 * @param tsk_lst, the head of the queue
 * @return the last task
*/
struct task *last_Task(taskList *tsk_lst);

/**
 * @brief dequeues a task from the queue
 * 
 * Takes the first the task of the queue
 * then unlinks the task and links the next in queue to the head
 * 
 * @param taskPool, the main struct used for getting the head of the queue
 * @return the first task of the queue
*/
struct task *dequeue_Task(TaskQueue *taskPool);

/**
 * @brief enqueues a task to the queue
 * 
 * Creates a new task with the parameters and places it 
 * last in the queue and links it to the other.
 * 
 * @param dirID, id to it's directory
 * @param file_name, the path to the file 
 * @param taskPool, the main struct used for getting the head of the queue
*/
void enqueue_Task(int dirID, char *file_name, TaskQueue *taskPool);

/**
 * @brief Deallocates the task
 * 
 * @param tsk_lst_pos, the task
*/
void destroy_Task(struct task *tsk_lst_pos);

/**
 * @brief Checks if two tasks are equal
 * 
 * @param task1
 * @param task2
 * @return true if they are equal, false if they are not
*/
bool task_equal(struct task *task1, struct task *task2);

/**
 * @brief Checks if the queue is empty
 * 
 * @param task_list, the head of the queue
 * @return true if the queue is empty, false if it isn't
*/
bool taskList_is_empty(taskList *task_list);

/**
 * @brief Initiliazes a Directory struct 
 * 
 * @param directory_name, the name of the argument
 * @param ID,
 * @return dir, the directory struct
*/
Directory *insert_Directory(char *directory_name, int ID);

/**
 * @brief Initiliazes a TaskQueue struct
 * 
 * @return taskPool, the TaskQueue struct
*/
TaskQueue *init_TaskQueue(void);

/**
 * @brief Gets the arguments and places them as directories and tasks
 * 
 * Gets the arguments and places them as directories this is used for the summation of 
 * of all the files or single file.
 * Then places these in a queue aswell to be used in the main algorithm
 *  
 * @param argc, the amount of arguments
 * @param argv, the arguments
 * 
 * @return taskPool, the struct used by all threads
*/
TaskQueue *get_tasks(int argc, char *argv[]);

/**
 * @brief Checks if the flag j is used
 * 
 * Checks if the flag j is in the arguments
 * if it is then gets the number after j
 * to be used as the amount of threads to be created.
 * 
 * @param argc, the amount of arguments
 * @param argv, the arguments
 * 
 * @return jflag
*/
int check_flag(int argc, char *argv[]);

/**
 * @brief Safely allocates memory for a variable
 * 
 * @param amount_of_blocks, Indicates how many blocks the user wants to allocate
 * @param block_size, Indicates the size of these blocks
 * 
 * @return , The adress of the allocated memory
*/
void *safe_malloc(size_t size);

/**
 * @brief the main function for deallocation
 * 
 * Uses remove_Task to deallocate the queue of tasks
 * and uses destroy_Dir to deallocate the directories
 * 
 * then deallocates everything else
 * 
 * @param taskPool, the struct to be deallocated
*/
void destroy_TaskQueue(TaskQueue *taskPool);

/**
 * @brief deallocates the directory
 * 
 * @param dir, the directory
*/
void destroy_Dir(Directory *dir);

#endif