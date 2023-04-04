/**
 * @file huffman.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "huffman.h"


int main(int argc, char *argv[])
{
    FILE *file_1 = malloc(sizeof(FILE));
    print_amount_bytes_before(argc, argv);
    pqueue *analysis = analyze_frequency(argc, argv, file_1);

    //calculate_and_print_amount_of_bytes(analysis, argc, argv);

    //print_and_empty(analysis);

    struct trie_node *root = create_huffman(analysis);
    //print_and_empty(analysis);
    int arr[256], n = 0;

    printf("%c", root->left_child->data);

    print_binary_codes(root, arr, n);
    return 0;
}






void print_and_empty(pqueue *pq)
{
	queue_elem *q_elem;

	printf("\nThe elements in the queue:\n");

	while (!pqueue_is_empty(pq))
    {
		q_elem = (queue_elem *)pqueue_inspect_first(pq);
		pqueue_delete_first(pq);
		printf("(%d, %c) \n",q_elem->freq, q_elem->character);
		free(q_elem);
	}
	printf("\n");
}

void calculate_and_print_amount_of_bytes(pqueue *pq, int argc, char *argv[])
{
    int freq = 0;

    queue_elem *q_elem;

    while (!pqueue_is_empty(pq))
    {
        q_elem = (queue_elem *)pqueue_inspect_first(pq);
        pqueue_delete_first(pq);

        freq += q_elem->freq;

        free(q_elem);
    }
    printf("%d bytes read from %s\n", freq, argv[1]);
}

void print_amount_bytes_before(int argc, char *argv[])
{
    FILE *in;
    int bytes;
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Could not open input file %s\n", argv[1]);
    }
    for(bytes = 0; getc(in) != EOF; bytes++);
    printf("%d bytes read from %s\n", bytes, argv[1]);

}
