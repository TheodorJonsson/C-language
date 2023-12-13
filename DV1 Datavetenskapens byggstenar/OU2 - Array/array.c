#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *array_create(int n1, int n2)
{
  Array *arr = malloc(sizeof(Array));

  arr->n1 = n1;
  arr->n2 = n2;
  arr->data = calloc(n1*n2, sizeof(int));

  return arr;
}

void array_destroy(Array *arr)
{
  free(arr->data);
  free(arr);
}

int array_rows(const Array *arr)
{
  return arr->n1;
}

int array_columns(const Array *arr)
{
  return arr->n2;
}

int array_get(const Array *arr, int i1, int i2)
{
  return arr->data[i1 * arr->n2 +i2];
}

void array_set(Array *arr, int i1, int i2, int value)
{
  arr->data[i1 * arr->n2 + i2] = value;
}
