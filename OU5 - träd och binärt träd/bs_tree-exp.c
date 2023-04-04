/* This program is intended to be run on a Linux-based operating system. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

#include "bs_tree.h"


// Declarations of functions.
static double get_time(void);
void swap(int *a, int *b);
void insert_value(int value, BSTreePos first_pos);
BSTreePos search_value(int value, BSTreePos first_pos);


int main(void)
{
	/* Print information about the program. */
	printf("EXPERIMENT PÅ BINÄRT SÖKTRÄD\n"
	"======================================================================\n"
	"\n"
	"Det här programmet mäter den genomsnittliga tiden det tar att söka \n"
	"efter ett värde i ett binärt sökträd. Antalet element som stoppas in \n"
	"i trädet kan varieras med avseende på start- och slutvärde och ökning \n"
	"mellan olika försök. Även antalet upprepningar kan varieras. Den totala \n"
	"tiden mäts och delas med antalet sökta värden. Resultaten presenteras i \n"
	"textformat på stdout med tab-separerade kolumner. Tiden mäts i \n"
	"nanosekunder.\n"
	"\n"
	"RESULTAT\n"
	"======================================================================\n"
	"\n");

	bool error = false;        /* Used as an error-flag. */
	int start_no_of_val = 0; /* The number of values in the smallest tree. */
	int end_no_of_val = 10000;  /* The number of values in the largest tree. */
	int inc_no_of_val = 100;   /* The size of increments of values. */
	int no_of_repeats = 100;    /* The number of runs for each size of the tree. */
	srand(time(0));

	/* Print table header. */
	printf("%14s\t%14s\n", "Antal element", "Tid/insättning");

	/* Loop over different number of values in the binary search tree */
	for (int n = start_no_of_val ; n <= end_no_of_val ; n += inc_no_of_val) {
		/* Repeat each experiment several times */
		double final_T = 0;
		for (int experiment = 0 ; experiment < no_of_repeats ; experiment++) {
			/* Create data */
			int arr[n];
			for (int i = 0 ; i < n ; i++) {
				arr[i] = i + 1;
			}

			/* Shuffle the values in the array. */
			for (int i = n - 1 ; i > 0 ; i--) {
				int j = rand() % i;
				swap(&arr[j], &arr[i]);
			}

			/* Create a binary search tree and insert the values in the array. */
			BSTree *tree = bs_tree_make(arr[0]);
			for (int i = 1 ; i < n ; i++) {
				BSTreePos pos = bs_tree_root(tree);
				insert_value(arr[i], pos);
			}

			/* Search for values in the binary search tree. */
			double T = get_time();
			for (int i = 0 ; i < n ; i++) {
				BSTreePos pos = bs_tree_root(tree);
				if (search_value(arr[i], pos) == NULL) {
					error = true;
				}
			}
			T = get_time() - T;
			T /= n; 			/* Compute average time per searched value. */
			T *= 1e9; 		/* Convert to nanoseconds. */
			final_T += T;	/* Sum the time for each repeat. */

			bs_tree_destroy(tree);

		}
		final_T /= no_of_repeats;	/* Compute average time per repeat. */
		if (!error) {
			/* Print the results for this number of values. */
			printf("%14d\t%14.2lf\n", n, final_T);
			fflush(stdout);
		} else {
			printf("At least one value could not be found\n");
		}
	}
}


/* Return the current time in seconds with high precision. */
static double get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, 0); 	/* Defined in POSIX (not standard C). */
	return tv.tv_sec + tv.tv_usec * 1e-6;
}


/* Swap the values. */
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


/* Insert a value in to the binary search tree. */
void insert_value(int value, BSTreePos pos)
{
  BSTreePos current = pos;
  BSTreePos previous = NULL;

  while(current != NULL)
  {
    previous = current;
    if(value < bs_tree_inspect_label(current))
    {
      current = bs_tree_left_child(current);
    }
    else
    {
      current = bs_tree_right_child(current);
    }
  }

  if(value < bs_tree_inspect_label(previous))
  {
    bs_tree_insert_left(value, previous);
  }
  else
  {
    bs_tree_insert_right(value, previous);
  }
}


/* Search for a specified value in the search tree. */
BSTreePos search_value(int value, BSTreePos pos)
{
  BSTreePos current = pos;

  while(current != NULL)
  {
    if(value == bs_tree_inspect_label(current))
    {
      return current;
    }
    if(value < bs_tree_inspect_label(current))
    {
      current = bs_tree_left_child(current);
    }
    else
    {
      current = bs_tree_right_child(current);
    }
  }
  return NULL;
}
