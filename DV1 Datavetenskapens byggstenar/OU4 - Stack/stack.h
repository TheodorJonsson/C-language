#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
/**
 * @defgroup stack my stack
 *
 * @brief Specification of the datatype stack
 *
 * Lets the user create a stack and input values.
 * Stack is a first in last out system. Meaning the first value
 * you input using push will the the last value that comes out of pop.
 *
 * @author Theodor Jonsson
 * @{
 */

/**
* @brief the type of a stack
*
* capacity, the max size of the stack
*
* size, the current size of the stack
*
* data, is the array of the stack
*/
typedef struct stack
{
    int capacity;
    int size;
    double *data;
} Stack;


/**
* @brief Creates an empty stack
*
* Creates a new stack and allocates the memory for it.
* sets the max capacity to 2 and the size to 0.
*
* @param -
*
* @return s, the empty stack
*/
Stack *stack_create(void);


/**
* @brief Destroy the stack
*
* Deallocates the memory of the data in the stack first
* then deallocates the memory of the stack
*
* @param s, the stack
*
* @return -
*/
void stack_destroy(Stack *s);

/**
* @brief Push a value onto the stack
*
* Given a stack and a value. first check if the stack is
* nearing max capacity if it is then double the size of the max capacity.
* Then inserts the given value on top of the stack
*
* @param s, the stack
* @param value, a float value
*
* @return -
*/
void stack_push(Stack *s, double value);


/**
* @brief Pop the value at the top of the stack
*
* Given a stack, gets the value at the top of the stack
* and assigns it to a new float, lastly removes the top of the stack
* then returns the copied float
*
* @param s, the stack
*
* @return top_of_stack, the copied float.
*/
double stack_pop(Stack *s);


/**
* @brief Check if the stack is empty
*
* Given a stack checks if
* the size of the stack is 0 if it is
* then returns true if not then returns false.
*
* @param s, the stack
*
* @return true if the stack is empty, false if it isn't.
*/
bool stack_is_empty(const Stack *s);

/**
 * @}
 */

#endif /* STACK_H */
