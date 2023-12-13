#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "set.h"
/**
 * @defgroup graph my Graph
 *
 * @brief Specification of the datatype Graph constructed as a Array of Set
 *
 * Lets the user create a graph with nodes that has values 0 to n-1.
 * The user can also insert edges between these nodes.
 * Lets the user get the set of neighbours in a node, also get the amount
 * of nodes in the entire graph.
 *
 * Lastly lets the user deallocate the graph.
 *
 * @author Theodor Jonsson
 * @{
 */

/**
* @brief the type for a node
*
* node, which is a set
*
* visit is bool to check if the node has been visited or not
*
* neighbours, which are the set of neighbours to the node
*
*/
typedef struct node
{
  int value;
  bool visit;
  set *neighbours;
} Node;

typedef struct graph
{
  int amount_of_nodes;
  Node *Nodes;
} Graph;
/**
* @brief Creates a graph
*
* Creates a graph with values ranging from
* 0 to value - 1. Value comes from the parameter.
* This graph has no edges
*
* @param value,
*
* @return g, the newly created graph
*/
Graph *graph_make(int value);

/**
* @brief Inserts a edge in the nodes
*
* Inserts the value from b to the set of neighbours in a
*
*
* @param a, which is the first node
* @param b, which is the second node
*
* @return -
*/
void graph_insert_edge(Node a, Node b);

/**
* @brief gets the neighbours of a node
*
* returns the set of neighbours in the node
*
* @param g, which is the node
*
* @return s, which is the neighbours to the node from the parameter
*/
set *get_neighbours(Node *a);

/**
* @brief gets the amount of nodes in a graph
*
*
* @param g, which is the graph
*
* @return the amount of nodes in the graoh
*/
int get_no_of_nodes(Graph *g);

/**
* @brief destroys the graph
*
* Firstly deallocates the sets in the array of Nodes
* then deallocates the Nodes and lastly dealocates the graph
*
* @param g, which is the graph
*
* @return -
*/
void graph_destroy(Graph *g);
/**
 * @}
 */

#endif /* SET_H */
