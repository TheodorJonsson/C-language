#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "list.h"
/**
 * @defgroup queue my Queue
 *
 * @brief Specification of the datatype queue created using list
 *
 * Lets the user create a queue and input values.
 * Stack is a first in first out system. Meaning the first value
 * you input using enqueue will the the first value
 * that comes out of when you use dequeue.
 *
 * @author Theodor Jonsson
 * @{
 */


/**
* @brief the type for the queue.
*
* list, is as pointer to list,
* which is a head of a list.
*/
typedef struct queue
{
    List *list;
} Queue;


/**
 * @brief Creates a empty queue
 *
 * Creates a queue and allocates the memory for it
 * then creates a head to point to itself
 * and nulls the value of the head
 *
 *
 * @param -
 *
 * @return empty queue
 */
Queue *queue_create(void);


/**
 * @brief Deallocates the queue
 *
 * Given a queue
 * Checks if the queue has any values
 * if it has any values deallocates them first
 * then deallocates the queue.
 *
 *
 * @param *q, a pointer to a Queue.
 *
 * @return -
 */
void queue_destroy(Queue *q);


/**
 * @brief Adds a value to the tail of the queue
 *
 * Given a queue and a value goes to the last
 * position of the queue and insert the given value
 *
 *
 * @param *q, a pointer to a Queue.
 * @param *value, a constant char array;
 *
 * @return -
 */
void queue_enqueue(Queue *q, const char *value);


/**
 * @brief Removes the value at the head of the queue
 *
 * Given a queue goes to the first position of the queue
 * and copies the value then removes the position and value.
 * Lastly returns the copied value.
 *
 * The caller is responsible for deallocating the returned pointer.
 * @param *q, the queue.
 *
 * @return string, the copied value.
 */
char *queue_dequeue(Queue *q);


/**
* @brief Check if the queue is empty
*
* Given a Queue checks if its empty and returns
* either true of false
*
* @param q, the queue
*
* @return true if the queue is empty, false if it isn't.
*/
bool queue_is_empty(const Queue *q);

/**
 * @}
 */

#endif /* QUEUE_H */
