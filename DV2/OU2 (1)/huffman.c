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
  if(argc < 4)
  {
    printf("USAGE:\n");
    printf("%s [OPTION] [FILE0] [FILE1] [FILE2]\n", argv[0]);
    printf("-encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
    printf("-decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
  }


  if(strcmp(argv[1], "-encode") == 0)
  {
    encode(argc, argv);
  }
  if(strcmp(argv[1], "-decode") == 0)
  {
    decode(argc, argv);
    printf("File succesfully decodes.");
  }
  return 0;

}

void encode(int argc, char *argv[])
{
  FILE *file_1 = malloc(sizeof(FILE));
  FILE *file_2 = malloc(sizeof(FILE));

  pqueue *analysis = analyze_frequency(argc, argv);
  struct trie_node *root = create_huffman_trie(analysis);
  Huffman_table *hufftab = malloc(255*sizeof(Huffman_table));
  bit_buffer *bitbuffer = bit_buffer_empty();

  print_amount_bytes_before(argc, argv);
  get_binary_codes(root, bitbuffer, hufftab);
  print_binary_codes_to_file(hufftab, argc, argv, file_1, file_2);
  print_amount_bytes_after(argc, argv);

  destroy_trie(root);
  free(bitbuffer);
  destroy_huffman_table(hufftab);
  free(hufftab);

  if(file_1 != NULL)
  {
    fclose(file_1);
  }
  if(file_2 != NULL)
  {
    fclose(file_2);
  }
}

void decode(int argc, char *argv[])
{
  FILE *file_1 = malloc(sizeof(FILE));
  FILE *file_2 = malloc(sizeof(FILE));

  pqueue *analysis = analyze_frequency(argc, argv);
  struct trie_node *root = create_huffman_trie(analysis);

  search_through_trie_and_print_to_file(root, argc, argv, file_1, file_2);

  destroy_trie(root);
  if(file_1 != NULL)
  {
    fclose(file_1);
  }
  if(file_2 != NULL)
  {
    fclose(file_2);
  }
}

void print_amount_bytes_before(int argc, char *argv[])
{
    FILE *file_1;
    int bytes;
    file_1 = fopen(argv[3], "r");
    if (file_1 == NULL)
    {
        printf("Could not open input file %s\n", argv[3]);
    }
    for(bytes = 0; getc(file_1) != EOF; bytes++);
    printf("%d bytes read from %s\n", bytes, argv[3]);

}

void print_amount_bytes_after(int argc, char *argv[])
{
    FILE *file_2;
    int i, bytes = 0;
    file_2 = fopen(argv[4], "r");
    if (file_2 == NULL)
    {
        printf("Could not open the output file %s\n", argv[4]);
        return;
    }
    for(i = 0; getc(file_2) != EOF; i++)
    {
      if(i % 8 == 0)
      {
        bytes++;
      }
    }

    printf("%d bytes read from %s\n", bytes, argv[4]);

}




void print_binary_codes_to_file(Huffman_table *hufftab, int argc, char *argv[],
                                                   FILE *file_1, FILE *file_2)
{
  int input;
  file_1 = fopen(argv[3], "r");
  if(file_1 == NULL)
  {
    printf("Could not open the input file %s\n", argv[3]);
    return;
  }
  file_2 = fopen(argv[4], "w");
  if(file_2 == NULL)
  {
    printf("Could not open the output file %s\n", argv[4]);
    return;
  }
  do
  {
    input = getc(file_1);
    if(input != EOF)
    {
      int value = search_value_in_huffman_table(hufftab, input);
      int size = bit_buffer_size(hufftab[value].byte_code);
      for(int j = 0; j <= size; j++)
      {
        fprintf(file_2, "%d", bit_buffer_inspect_bit(hufftab[value].byte_code, j));
      }
    }
  } while(input != EOF);

  int value = search_value_in_huffman_table(hufftab, 4);
  int size = bit_buffer_size(hufftab[value].byte_code);
  for(int i = 0; i <= size; i++)
  {
    fprintf(file_2, "%d", bit_buffer_inspect_bit(hufftab[value].byte_code, i));
  }

}
