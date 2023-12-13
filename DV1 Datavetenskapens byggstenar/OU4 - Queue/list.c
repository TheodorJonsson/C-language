#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
* clone_string
* Description: determines the size of the given char
* then allocates the adequate amount of memory for
* a new char and then copies the given char to the new char
*
* Input: a pointer to a constant char
* Output: the copied char
*/
static char *clone_string(const char *in)
{
  size_t len = strlen(in);
  char *out = calloc(len + 1, sizeof(char));
  strcpy(out, in);
  return out;
}

/*
* make_node
* Description: creates a new node and allocates the memory for it
* assigns the value of the given char using the function clone_string
*
*
* Input: a pointer to a constant char
* Output: a created node
*/
static struct node *make_node(const char *value)
{
  struct node *newNode = malloc(sizeof(struct node));

  newNode->value = clone_string(value);
  return newNode;
}

List *list_create(void)
{
  List *head = malloc(sizeof(struct list));

  head->head.prev = &head->head;
  head->head.next = &head->head;
  head->head.value = NULL;

  return head;
}

void list_destroy(List *lst)
{
  ListPos pos = list_end(lst);
  while(list_is_empty(lst) == false)
  {
    pos = list_prev(pos);
    pos = list_remove(pos);
  }
  free(lst);
}

bool list_is_empty(const List *lst)
{
  if(lst->head.next == &lst->head)
  {
    return true;
  }
  else
  {
    return false;
  }
}

ListPos list_first(List *lst)
{
  ListPos pos = {
    .node = lst->head.next
  };
  return pos;
}

ListPos list_end(List *lst)
{
  ListPos pos = {
    .node = &lst->head
  };
  return pos;
}

bool list_pos_equal(ListPos p1, ListPos p2)
{
  if (p1.node == p2.node)
  {
    return true;
  }
  return false;
}

ListPos list_next(ListPos pos)
{
  pos.node = pos.node->next;
  return pos;
}

ListPos list_prev(ListPos pos)
{
  pos.node = pos.node->prev;
  return pos;
}

ListPos list_insert(ListPos pos, const char *value)
{
  // Create a new node.
  struct node *node = make_node(value);

  // Find nodes before and after (may be the same node: the head of the list).
  struct node *before = pos.node->prev;
  struct node *after = pos.node;

  // Link to node after
  node->next = after;
  after->prev = node;

  // Link to node before.
  node->prev = before;
  before->next = node;

  // Return the position of the new element.
  pos.node = node;
  return pos;
}

ListPos list_remove(ListPos pos)
{
  // Save pointer to node
  struct node *before = pos.node->prev;
  struct node *after = pos.node->next;
  // Unlink node
  before->next = after;
  after->prev = before;
  // free value and node
  free(pos.node->value);
  free(pos.node);
  // return the position of the next element
  pos.node = after;
  return pos;
}

const char *list_inspect(ListPos pos)
{
  return pos.node->value;
}
