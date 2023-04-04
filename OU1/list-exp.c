/* This program is intended to be run on a Linux-based operating system. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "list.h"


/* Return the current time in seconds with high precision. */
static double get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, 0); 	/* Defined in POSIX (not standard C). */
	return tv.tv_sec + tv.tv_usec * 1e-6;
}


int main(void)
{
	const int n_min = 100;
	const int n_max = 100000000;
	const float n_fact = 1.2;
	const char *value = "Test string";

	/* Print information about the program. */
	printf("EXPERIMENT PÅ LISTA\n"
	"======================================================================\n"
	"\n"
	"Det här programmet mäter tiden det tar att sätta in n värden i en\n"
	"lista. Experimentet omfattar många olika problemstorlekar och\n"
	"resultaten presenteras i textformat på stdout med tab-separerade\n"
	"kolumner. Tiden mäts i sekunder.\n"
	"\n"
	"RESULTAT\n"
	"======================================================================\n"
	"\n");

	/* Print table header. */
	printf("%10s\t%10s\n", "n", "tid");

	/* Loop over problem sizes. */
	for (int n = n_min; n <= n_max; n *= n_fact) {
		List *lst = list_create();

		/* Insert n values at the beginning of the list. */
		double T = get_time();
		for (int k = 0; k < n; k++) {
			ListPos pos = list_first(lst);
			list_insert(pos, value);
		}
		T = get_time() - T;

		list_destroy(lst);

		/* Print the results for this problem size. */
		printf("%10d\t%10.6lf\n", n, T);

		/* Abort when the time is starting to get significant. */
		if (T > 1) {
			break;
		}
	}
}
