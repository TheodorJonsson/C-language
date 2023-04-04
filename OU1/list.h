#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
/**
 * @defgroup list my list
 *
 * @brief Specification of a doubly linked list
 *
 * Lets the user create a list and input values.
 * Also lets the user navigate through the list and compare
 * positions and remove positions and values.
 *
 * @{
 */

/**
* @brief the type for a node in the list.
*
* *next is a pointer to a node
* which will point to the next element in the list.
*
* *prev is a pointer to a node.
* which will point to the previous element in the list.
*
* *value is a pointer to a char.
* which will point to the value of the element
*/
struct node
{
  struct node *next;
  struct node *prev;
  char *value;
};

/**
* @brief the type for a list.
*
* head is a struct node.
*/
typedef struct list
{
  struct node head;
} List;

/**
* @brief the type for a list position
*
* *node is a pointer to a node.
*/
typedef struct list_pos
{
  struct node *node;
} ListPos;

/**
 * @brief Creates a empty list
 *
 * Allocates the memory for a List head
 * Then points the head to itself
 * and nulls the value of the head
 *
 * @param -
 *
 * @return empty list
 */
List *list_create(void);


/**
 * @brief Deallocates the list
 *
 * Checks if the list has any values
 * if any values deallocate them first
 * then deallocates the list
 *
 * @param *lst, a pointer to a List.
 *
 * @return -
 */
void list_destroy(List *lst);


/**
 * @brief frees the memory of the list
 *
 * Goes through the list from start to end
 * and removes the values in each nodes
 * until there is only the head left. Then
 * it frees the memory of the list
 *
 * @param *lst, a pointer to a constant List.
 *
 * @return true or false value
 */
bool list_is_empty(const List *lst);


/**
 * @brief Get the position of the first element.
 *
 * Given a list and creating a new ListPos pos
 * using the head of the list to assign its
 * next value to the newly created ListPos
 *
 * @param *lst, a pointer to a List.
 *
 * @return pos, the first element in the list
 */
ListPos list_first(List *lst);


/**
 * @brief Get the position after the last element.
 *
 * Given a list and creating a new ListPos
 * using the head of the list to assign its
 * value to the newly created ListPos
 *
 * @param *lst, a pointer to a List.
 *
 * @return pos, the head of the list
 */
ListPos list_end(List *lst);


/**
 * @brief Check equality between two positions
 *
 * Given two positions and checking if these two
 * nodes are equal
 *
 * @param ListPos p1.
 * @param ListPos p2.
 *
 * @return true or false
 */
bool list_pos_equal(ListPos p1, ListPos p2);


/**
 * @brief Forward to the next position
 *
 *
 *
 * @param ListPos pos, the position of the list.
 *
 *
 * @return pos, position of the next element
 */
ListPos list_next(ListPos pos);

// Backward to the previous position.
/**
 * @brief Backward to the previous position
 *
 *
 *
 * @param ListPos pos, the position of the list.
 *
 *
 * @return pos, position of the previous element
 */
ListPos list_prev(ListPos pos);


/**
 * @brief Insert the value before the position
 *
 * Given a element and a value, creates a new node using a internal function
 * then creates two other nodes to hold the position of the given position.
 * Links the node to the given positions
 *
 * @param ListPos pos, the position of the list.
 *
 * @return pos, position of the new element
 */
ListPos list_insert(ListPos pos, const char *value);


/**
 * @brief Remove the value at the position
 *
 * Saves the pointers of the given element to new nodes.
 * Unlinks the given element and the frees the vlue of the element
 * then frees the element aswell
 *
 * @param ListPos pos, the position of the list.
 *
 * @return pos, position of the next element
 */
ListPos list_remove(ListPos pos);


// Get the value of at the position.
/**
 * @brief Get the value at the position
 *
 *
 * @param ListPos pos, the position of the list.
 *
 * @return pos.node->value, the char of the given element
 */
const char *list_inspect(ListPos pos);
/**
 * @}
 */

#endif /* LIST_H */
