#include <stdio.h>
#include "stack.h"

int main(void)
{
    // Create an empty stack.
    Stack *s = stack_create();

    // Push some values.
    for (int i = 0; i < 10; i++) {
        stack_push(s, i);
    }

    // Pop and print.
    while (!stack_is_empty(s)) {
        printf("%8.2lf\n", stack_pop(s));
    }

    // Clean up.
    stack_destroy(s);
    printf("it worked?\n");
    return 0;
}
