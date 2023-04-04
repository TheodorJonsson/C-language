#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

Graph *graph_make(int value)
{
  Graph *g = malloc(sizeof(struct graph));
  g->amount_of_nodes = value;
  g->Nodes = calloc(value, sizeof(struct node));

  for (int i = 0; i < value; i++)
  {
    g->Nodes[i].value = i;
    g->Nodes[i].visit = false;
    g->Nodes[i].neighbours = set_empty();
  }

  return g;
}


void graph_insert_edge(Node a, Node b)
{
  set_insert(b.value ,a.neighbours);
}

set *get_neighbours(Node *a)
{
  set *s = a->neighbours;
  return s;
}

int get_no_of_nodes(Graph *g)
{
  return g->amount_of_nodes;
}

void graph_destroy(Graph *g)
{
  for(int i = 0; i < g->amount_of_nodes; i++)
  {
    set_destroy(g->Nodes[i].neighbours);
  }
  free(g->Nodes);
  free(g);
}
