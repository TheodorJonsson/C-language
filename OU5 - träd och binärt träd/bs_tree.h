#ifndef BS_TREE_H
#define BS_TREE_H

#include <stdbool.h>
/**
 * @defgroup bs_tree my Binary search tree
 *
 * @brief Specification of the datatype Binary search tree.
 *
 * Lets the user create a binary search tree and input values as integers
 * in nodes with a left and a right child. Lets the user check if
 * the nodes has children and insert new nodes to these children.
 * Lastly lets the user deallocate the tree.
 *
 *
 * @author Theodor Jonsson
 * @{
 */

/**
* @brief the type for the node.
*
* value, holds the value of the node in an integer.
*
* left_child, pointer to the left child
* which is also a node.
*
* right_child, pointer to the right child
* which is also a node.
*/
struct node
{
    int value;
    struct node *left_child;
    struct node *right_child;
};


/**
* @brief the type for a BSTree.
*
* Which is a node but makes the code easier to read.
*/
typedef struct node BSTree;


/**
* @brief the type for BSTreePos.
*
* Which is pointer to a node to hold the position in the BSTree.
*/
typedef struct node* BSTreePos;


/**
* @brief Creates a Binary search tree
*
* Creates a binary search tree and assigns the value from the paramater.
* Then NULLs the left and right child.
*
* @param value, an integer to assign the first node a value.
*
* @return root, which is the root of the tree with value of the parameter.
*/
BSTree *bs_tree_make(int value);


/**
* @brief Creates a new node and insert it to the left child
*
* Creates a new node and assigns its value from the parameter
* then NULLs it child pointers lastly assigns the new node to
* the left child from the pos in the paramater.
*
* @param value, an integer to assign the new a value.
* @param pos, the parent of the newly created node.
*
* @return the position of the newly created node.
*/
BSTreePos bs_tree_insert_left(int value, BSTreePos pos);


/**
* @brief Creates a new node and insert it to the right child
*
* Creates a new node and assigns its value from the parameter
* then NULLs it child pointers lastly assigns the new node to
* the right child from the pos in the paramater.
*
* @param value, an integer to assign the new a value.
* @param pos, the position of the parent of the newly created node.
*
* @return the position of the newly created node.
*/
BSTreePos bs_tree_insert_right(int value, BSTreePos pos);


/**
* @brief Gets the value at the position
*
* Checks the value of the node from the parameter and returns it
* as an integer.
*
* @param pos, the position of the node.
*
* @return the value of the node.
*/
int bs_tree_inspect_label(BSTreePos pos);


/**
* @brief Check if the node at the position has a left child.
*
*
* @param pos, the position of the parent node.
*
* @return true if the node has a left child false if it doesn't.
*/
bool bs_tree_has_left_child(BSTreePos pos);


/**
* @brief Check if the node at the position has a right child.
*
*
* @param pos, the position of the parent node.
*
* @return true if the node has a right child false if it doesn't.
*/
bool bs_tree_has_right_child(BSTreePos pos);


/**
* @brief Get the position of the root.
*
* Converts the tree to a position of a tree which is the root
* then returns the position
*
* @param tree, which is the binary search tree
*
* @return root, which is the position of the first node
*/
BSTreePos bs_tree_root(BSTree *tree);


/**
* @brief Get the position of the left child.
*
* Gets the position of the left child
* to the node from the parameter pos and returns the left child
*
* @param pos, the position of the parent node
*
* @return the position of the left child
*/
BSTreePos bs_tree_left_child(BSTreePos pos);


/**
* @brief Get the position of the right child.
*
* Gets the position of the right child
* to the node from the parameter pos and returns the right child.
*
* @param pos, the position of the parent node.
*
* @return the position of the right child.
*/
BSTreePos bs_tree_right_child(BSTreePos pos);


/**
* @brief Deallocate the binary search tree.
*
* Checks if the tree is empty or not.
* Then goes through the tree recursively
* and deallocates every node
*
* @param pos, the position of the node
*
* @return -
*/
void bs_tree_destroy(BSTree *tree);

/**
 * @}
 */
#endif /* BS_TREE_H */
