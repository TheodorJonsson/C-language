#include <stdio.h>
#include "list.h"

static void add_values(List *lst);
static void print_forward(List *lst);

int main(void)
{
  List *lst = list_create();
  printf("1\n");
  add_values(lst);

  printf("2\n");

  print_forward(lst);
  printf("3\n");
}

static void add_values(List *lst)
{
  ListPos pos = list_first(lst);
  printf("1.1\n");
  pos = list_insert(pos, "Apple");
  printf("1.2\n");
  pos = list_next(pos);
  printf("1.3\n");
  //pos = list_insert(pos, "banan");
  printf("1.4\n");
}

static void print_forward(List *lst)
{
  printf("2.1\n");
  ListPos pos = list_first(lst);
  //ListPos end = list_end(lst);
  printf("2.2\n");
  int i = 0;
  while(i <= 2)
  {
    const char *str = list_inspect(pos);
    printf("2.2.%d\n", i);
    printf("Value: %s\n", str);
    pos = list_next(pos);
    i++;
  }
}
