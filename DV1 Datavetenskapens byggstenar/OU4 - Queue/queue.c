#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

Queue *queue_create(void)
{
  Queue *q = malloc(sizeof(Queue));
  q->list = list_create();

  return q;
}

void queue_destroy(Queue *q)
{
  list_destroy(q->list);
  free(q);
}

void queue_enqueue(Queue *q, const char *value)
{
  ListPos pos = list_end(q->list);
  list_insert(pos, value);
}

char *queue_dequeue(Queue *q)
{
  ListPos pos = list_first(q->list);
  const char *last = list_inspect(pos);
  char *string = malloc(1 + sizeof(strlen(last)));

  strcpy(string, last);
  list_remove(pos);

  return string;
}

bool queue_is_empty(const Queue *q)
{
  if(list_is_empty(q->list))
  {
    return true;
  }
  return false;
}
