/* This program is intended to be run on a Linux-based operating system. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "table.h"


#define TABLE_CAPACITY 1000000


/* Return the current time in seconds with high precision. */
static double get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, 0); 	/* Defined in POSIX (not standard C). */
	return tv.tv_sec + tv.tv_usec * 1e-6;
}


int main(void)
{
	/* Print information about the program. */
	printf("EXPERIMENT PÅ TABELL\n"
	"======================================================================\n"
	"\n"
	"Det här programmet mäter den genomsnittliga tiden det tar att sätta in\n"
	"element i en hashtabell. Fyllnadsgraden varieras från 0,2%% till\n"
	"99,8%%. Element med randomiserade nycklar sätts in i en tom tabell\n"
	"tills den efterfrågade fyllnadsgraden uppnåtts. Den totala tiden mäts\n"
	"och delas med antalet insatta element. Resultaten presenteras i\n"
	"textformat på stdout med tab-separerade kolumner. Tiden mäts i\n"
	"nanosekunder. Fyllnadsgraden mäts i procent.\n"
	"\n"
	"RESULTAT\n"
	"======================================================================\n"
	"\n");

	/* Do a warm-up phase followed by the actual experiment. */
	for (int phase = 0; phase < 2; phase++) {
		if (phase == 0) {
			printf("Värmer upp...");
			fflush(stdout);
		} else {
			/* Print table header. */
			printf("%14s\t%10s\n", "fyllnadsgrad", "tid");
		}

		/* Loop over fill percentages. */
		for (float percent = 0.2; percent <= 99.8; percent += 0.2) {
			const int n = TABLE_CAPACITY / 100 * percent;

			Table *tab = table_create(TABLE_CAPACITY);

			/* Insert random key/value-pairs. */
			double T = get_time();
			for (int k = 0; k < n; k++) {
				const int key = rand();
				const int value = k;
				table_insert(tab, key, value);
			}
			T = get_time() - T;
			T /= n; 			/* Compute average time per insertion. */
			T *= 1e9; 			/* Convert to microseconds. */

			table_destroy(tab);

			if (phase != 0) {
				/* Print the results for this fill percentage. */
				printf("%14.2lf\t%10.2lf\n", percent, T);
				fflush(stdout);
			}
		}
		if (phase == 0) {
			printf("färdig\n\n");
		}
	}
}
