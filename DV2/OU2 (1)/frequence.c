/**
 * @file frequence.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "frequence.h"

/*------------------------Internal Functions--------------------------------*/
/* Function for comparing two prio-elements
 *
 * @param elem1 - the first value
 * @param elem2 - the second value
 *
 * @return > 0   if elem1 > elem2
 *         < 0   if elem1 < elem2
 *          0    if elem1 = elem2
 */
int lessthan(void *elem1, void *elem2)
{
    return ((queue_elem *)elem1)->freq - ((queue_elem *)elem2)->freq;
}
/**
* @brief gets the frequency of the characters.
*
* @param freq, which is the array to hold the frequencies.
* @param in, which is the file to be read from.
* @param argc, amount of arguments from command line.
* @param argv, arguments from command line.
*
* @return 1 if succesfully opens the file 0 if not.
*/
int get_frequency(int *freq, int argc, char *argv[])
{
  int input;
  FILE *file_0 = fopen(argv[2], "r");
  if (file_0 == NULL)
  {
    printf("Could not open input file %s\n", argv[2]);
    return 0;
  }
  do
  {
    input = getc(file_0);
    freq[input]++;
  } while ((input = getc(file_0)) != EOF);

  fclose(file_0);
  return 1;
}
/*---------------------------------------------------------------------------*/
pqueue *analyze_frequency(int argc, char *argv[])
{
  int *character = populate_int_array();
  int *freq = zero_array();
  queue_elem *q_elem;
  pqueue *pq = pqueue_empty(lessthan);

  int opened_file = get_frequency(freq, argc, argv);
  if(opened_file > 0)
  {
    for (int i = 0; i <= 255; i++)
    {
      q_elem = malloc(sizeof(q_elem));
      q_elem->freq = freq[i];
      q_elem->character = character[i];
      pqueue_insert(pq, q_elem);
    }
  }

  free(character);
  free(freq);
  return pq;
}


int *populate_int_array(void)
{
  int *character = malloc(255*sizeof(int));
  for (int i = 0; i <= 255; i++)
    {
      character[i] = i;
    }
    return character;
}

int* zero_array(void)
{
  int *freq = malloc(255*sizeof(int));
  for (int i = 0; i <= 255; i++)
  {
    freq[i] = 0;
  }
  return freq;
}
