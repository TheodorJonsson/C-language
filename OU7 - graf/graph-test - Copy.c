#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

void depth_first(Node *n, Graph *g);
void insert_random_arches(int max, Graph *g);
void print_neighbours(int max, Graph *g);
void visit(Node *n);
bool is_visited(Node *n);


int main(void)
{
  srand(time(NULL));
 //The amount nodes in the graph
  int n = 10;

  Graph *g = graph_make(n);

  insert_random_arches(n, g);

  depth_first(&g->Nodes[0], g);
  printf("\n");
  print_neighbours(n, g);

  graph_destroy(g);
}

/**
* @brief a Depth first algorithm
*
* Uses this algorithm to search through the graph
*__________________________________________
*| visit(n) // Marks node n as visited     |
*| neighbourSet = neighbours(n, g);        |
*| for each node v in g do                 |
*|   if v is a member of neighbourSet then |
*|     if not visited(v) then              |
*|       depthFirst(v, g)                  |
*|_________________________________________|
* Also prints out the steps it take through the graoh
*
*
* @param n, which is the node
* @param g, which is the graph
*
* @return -
*/
void depth_first(Node *n, Graph *g)
{
  visit(n);
  set *neighbourSet = get_neighbours(n);

  for (int i = 0; i < get_no_of_nodes(g) - 1; i++)
  {

    if(set_member_of(g->Nodes[i].value, neighbourSet))
    {


      if(is_visited(&g->Nodes[i]) == false)
      {
        printf(" %d ", g->Nodes[i].value);
        depth_first(&g->Nodes[i], g);

      }
    }
  }

}
/**
* @brief Inserts random arches in to the graph
*
* Generates two different random numbers from 0 to max - 1 to use for
* randomly selecting nodes in the array of nodes
* Checks so that a node doesn't become a neighbour to itself
*
* @param max, which is the max amount of nodes in the graph
* @param g, whichs is the graph
*
* @return -
*/
void insert_random_arches(int max, Graph *g)
{
  for (int i = 0; i < max*3; i++)
  {
    int rand1 = rand() % (max);
    int rand2 = rand() % (max);
    if(rand1 != g->Nodes[rand2].value)
    {
      graph_insert_edge(g->Nodes[rand1], g->Nodes[rand2]);
    }
  }
}


/**
* @brief Prints out the neighbours
*
* Uses function from set to get the neighbours of every set
* of neighbours in the graph to print them out
*
* @param max, which is the max amount of nodes in the graph
* @param g, whichs is the graph
*
* @return -
*/
void print_neighbours(int max, Graph *g)
{
  for(int i = 0; i < max - 1; i++)
  {
    set *neighbours = get_neighbours(&g->Nodes[i]);
    int *arr = set_get_values(neighbours);
    printf("%d: ", i);
    for(int j = 0; j < set_size(neighbours); j++)
    {
      printf(" %d", arr[j]);
    }
    printf("\n");
    free(arr);
  }
}

/**
* @brief visits the node
*
* assign true to the nodes boolean.
* @param n, which is the node
*
* @return -
*/
void visit(Node *n)
{
  n->visit = true;
}


/**
* @brief Checks if the node has been visited.
*
* @param n, which is the node
*
* @return true if the node has been visited, false if not
*/
bool is_visited(Node *n)
{
  if(n->visit == true)
  {
    return true;
  }
  return false;
}
