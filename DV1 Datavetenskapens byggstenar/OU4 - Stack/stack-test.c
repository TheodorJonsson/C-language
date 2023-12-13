#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "stack.h"

Stack *populate_stack(Stack *s);
bool verify_stack(Stack *s);

int main(void)
{
  Stack *s = stack_create();

  populate_stack(s);
  printf("Test the functioning of the stack ... ");
  if(verify_stack(s))
  {
    printf("PASS");
  }
  else
  {
    printf("FAIL");
  }

  stack_destroy(s);
  return 0;
}
/**
*  populates the table
*
* populates the stack using a for loop and stack_push
* then returns the populated stack
*
* param *s, the stack
*
* return s, the populated stack
*/
Stack *populate_stack(Stack *s)
{
  for(int i = 1; i <= 10; i++)
  {
    double num;
    num = pow(0.5, i);
    stack_push(s, num);
  }
  return s;
}
/**
* verifies the stacks
*
* using a while loop pops the values and check
* if they are the correct values. it does this until
* the stack is empty.
*
* param
* returns true or false
*/
bool verify_stack(Stack *s)
{
  int i = 10;
  while(!stack_is_empty(s))
  {
    double num;
    num = pow(0.5, i);
    i--;
    if(!(num == stack_pop(s)))
    {
      return false;
    }

  }
  return true;
}
