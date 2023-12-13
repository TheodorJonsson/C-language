#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "stack.h"

Stack *stack_create(void)
{
  int n = 8;
  Stack *s = malloc(sizeof(Stack));
  s->capacity = n;
  s->size = 0;
  s->data = malloc(n*sizeof(s->data));

  return s;
}

void stack_destroy(Stack *s)
{
  free(s->data);
  free(s);
}

void stack_push(Stack *s, double value)
{
  if(s->capacity - 1 == s->size)
  {
    int num = pow(2, s->capacity);
    s->data = realloc(s->data, num);
  }

  s->data[s->size] = value;
  s->size++;
}

double stack_pop(Stack *s)
{
  double top_of_stack;
  s->size--;
  top_of_stack = s->data[s->size];

  return top_of_stack;
}

bool stack_is_empty(const Stack *s)
{
  if(s->size == 0)
  {
    return true;
  }
  return false;
}
