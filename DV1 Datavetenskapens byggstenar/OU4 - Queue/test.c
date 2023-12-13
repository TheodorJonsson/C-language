#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "queue.h"

int main(void)
{
    // Create an empty queue.
    Queue *q = queue_create();

    // Add the values A, B, ..., Z to the queue.
    char str[] = "A";
    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        str[0] = ch;
        queue_enqueue(q, str);
    }

    // Verify the values in the queue.
    bool ok = true;
    for (char ch = 'A'; ch <= 'Z'; ch++)
     {
        str[0] = ch;
        char *str2 = queue_dequeue(q);
        printf(" %s%s ", str2, str);
        if (strcmp(str, str2) != 0)
        {
            ok = false;
        }
        free(str2);
    }

    if (!queue_is_empty(q))
    {
        ok = false;
    }
    printf("Test the functioning of the queue ... %s\n", ok ? "PASS" : "FAIL");

    // Clean up.
    queue_destroy(q);

    return 0;
}
