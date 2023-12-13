#include "bs_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bs_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Declarations of functions.
void print_array(int n, int a[]);
void swap(int *a, int *b);
void insert_value(int value, BSTreePos first_pos);
BSTreePos search_value(int value, BSTreePos first_pos);


int main(void)
{
  // Create an array with the values 1, 2, ..., 10 and print out the content.
  int n = 10;
  int arr[n];

  srand(time(0));

  for (int i = 0 ; i < n ; i++)
  {
    arr[i] = i + 1;
  }

  print_array(n, arr);

  // Shuffle the values in the array and print out the content.
  for (int i = n - 1 ; i > 0 ; i--)
  {
    int j = rand() % i;
    swap(&arr[j], &arr[i]);
  }

  print_array(n, arr);

  // Create a binary search tree and insert the values in the array.
  BSTree *tree = bs_tree_make(arr[0]);

  return 0;

}

// Print the array.
void print_array(int n, int a[])
{
    printf("Array: ");
    for (int i = 0 ; i < n ; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Swap the values.
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
