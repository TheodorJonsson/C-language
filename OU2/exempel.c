#include <stdio.h>
#include "array.h"


int main(void)
{
    // Create a zero array.
    Array *arr = array_create(4, 4);

    // Fill it with values 1...16.
    int cnt = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array_set(arr, i, j, cnt++);
        }
    }

    // Print it out in a 2D layout.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02d ", array_get(arr, i, j));
        }
        printf("\n");
    }

    // Clean up.
    array_destroy(arr);

    return 0;
}
