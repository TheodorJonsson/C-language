#include <stdio.h>
#include <stdbool.h>
#include "array.h"


// Fill the array row-wise with values from 1 to n1 * n2.
static void populate_array(Array *arr)
{
    int cnt = 1;
    int rows = array_rows(arr);
    int cols = array_columns(arr);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array_set(arr, i, j, cnt++);
        }
    }
}


// Verify the array's contents.
static bool verify_array(const Array *arr)
{
    int cnt = 1;
    int rows = array_rows(arr);
    int cols = array_columns(arr);
    bool correct = true;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (array_get(arr, i, j) != cnt++) {
                correct = false;
            }
        }
    }
    return correct;
}


int main(void)
{
    // Create a zero array with 5 rows and 20 columns.
    Array *arr = array_create(5, 20);

    // Fill the array with values 1...100.
    populate_array(arr);

    // Verify the array's contents.
    bool ok = verify_array(arr);
    printf("Test the functioning of the array ... %s\n", ok ? "PASS" : "FAIL");

    // Clean up.
    array_destroy(arr);

    return 0;
}
