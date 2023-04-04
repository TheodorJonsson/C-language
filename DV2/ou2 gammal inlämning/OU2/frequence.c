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

pqueue *analyze_frequency(int argc, char *argv[], FILE *in)
{
    char *character = populate_char_array();
    int *freq = zero_array();
    queue_elem *q_elem;
    pqueue *pq = pqueue_empty(lessthan);

    int opened_file = get_frequency(character, freq, in, argc, argv);
    if(opened_file > 0)
    {
        /*for (int i = 0; i <= 255; i++)
        {
          printf("Character = %c frequence = %d\n", character[i], freq[i]);
        }*/
        for (int i = 0; i <= 255; i++)
        {
            q_elem = malloc(sizeof(q_elem));
            q_elem->freq = freq[i];
            q_elem->character = character[i];
            pqueue_insert(pq, q_elem);
        }
    }

    return pq;
}


char* populate_char_array(void)
{
    char *character = malloc(255*sizeof(char));
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

int get_frequency(char *character, int *freq, FILE *in, int argc, char *argv[])
{
    char input;

    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Could not open input file %s\n", argv[1]);
        return 0;
    }
    do
    {
        input = getc(in);

        freq[(unsigned char)input]++;
    } while ((input = getc(in)) != EOF);

    return 1;
}
