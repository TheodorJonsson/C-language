/**
 * @file huffman.c
 * @author Theodor Jonsson (thedders2@hotmail.com, ens18trn@cs.umu.se)
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
  if(argc <= 4)
  {
    printf("USAGE:\n");
    printf("%s [OPTION] [FILE0] [FILE1] [FILE2]\n", argv[0]);
    printf("-encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
    printf("-decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
  }


  if(strcmp(argv[1], "-encode") == 0 && argc >= 5)
  {
    encode(argc, argv);
  }
  if(strcmp(argv[1], "-decode") == 0 && argc >= 5)
  {
    decode(argc, argv);
    printf("File succesfully decodes.");
  }

  return 0;

}

void encode(int argc, char *argv[])
{
  FILE *file_0 = malloc(sizeof(FILE));
  FILE *file_1 = malloc(sizeof(FILE));
  FILE *file_2 = malloc(sizeof(FILE));


  pqueue *analysis = analyze_frequency(argc, argv, file_0);
  struct trie_node *root = create_huffman_trie(analysis);
  Huffman_table *hufftab = malloc(255*sizeof(struct huffman_table));
  bit_buffer *bitbuffer = bit_buffer_empty();

  print_amount_bytes_before(argc, argv);
  printf("1\n");
  get_binary_codes(root, bitbuffer, hufftab);
  printf("1\n");
  print_binary_codes_to_file(hufftab, argc, argv, file_1, file_2);
  printf("1\n");
  print_amount_bytes_after(argc, argv);
  printf("1\n");

  bit_buffer_free(bitbuffer);
  destroy_huffman_table(hufftab);
  destroy_trie(root);

  /*free(root->left_child);
  free(root->right_child);
  free(root);*/
}

void decode(int argc, char *argv[])
{
  FILE *file_0 = malloc(sizeof(FILE));
  FILE *file_1 = malloc(sizeof(FILE));
  FILE *file_2 = malloc(sizeof(FILE));

  pqueue *analysis = analyze_frequency(argc, argv, file_0);
  struct trie_node *root = create_huffman_trie(analysis);

  search_through_trie_and_print_to_file(root, argc, argv, file_1, file_2);

  destroy_trie(root);

}

void print_amount_bytes_before(int argc, char *argv[])
{
    FILE *file_1;
    int bytes;
    file_1 = fopen(argv[3], "r");
    if (file_1 == NULL)
    {
        printf("Could not open input file %s\n", argv[3]);
        fclose(file_1);
    }
    for(bytes = 0; getc(file_1) != EOF; bytes++);
    printf("%d bytes read from %s\n", bytes, argv[3]);
    fclose(file_1);
}

void print_amount_bytes_after(int argc, char *argv[])
{
    FILE *file_2;
    int i, bytes = 0;
    file_2 = fopen(argv[4], "rb");
    if (file_2 == NULL)
    {
        printf("Could not open the output file %s\n", argv[4]);
        fclose(file_2);
        return;
    }
    for(bytes = 0; getc(file_2) != EOF; bytes++);


    printf("%d bytes read from %s\n", bytes, argv[4]);
    fclose(file_2);
}




void print_binary_codes_to_file(Huffman_table *hufftab, int argc, char *argv[],
                                                   FILE *file_1, FILE *file_2)
{
  int input;
  bit_buffer *inputbyte = bit_buffer_empty();
  file_1 = fopen(argv[3], "r");
  if(file_1 == NULL)
  {
    printf("Could not open the input file %s\n", argv[3]);
    fclose(file_1);
    return;
  }
  file_2 = fopen(argv[4], "wb");
  if(file_2 == NULL)
  {
    printf("Could not open the output file %s\n", argv[4]);
    fclose(file_1);
    fclose(file_2);
    return;
  }
  do
  {
    input = getc(file_1);
    if(input != EOF)
    {
      int value = search_value_in_huffman_table(hufftab, input);
      //char *output = bit_buffer_to_byte_array(hufftab[value].byte_code);
      for(int i = 0; i < bit_buffer_size(hufftab[value].byte_code); i++)
      {
        int bit = bit_buffer_inspect_bit(hufftab[value].byte_code, i);
        bit_buffer_insert_bit(inputbyte, bit);
      }
      //fprintf(file_2, "%s", output);
      //ree(output);
    }
  } while(input != EOF);
  int value = search_value_in_huffman_table(hufftab, 4);
  int size = bit_buffer_size(hufftab[value].byte_code);
  for(int i = 0; i <= size; i++)
  {
    int eotbit = bit_buffer_inspect_bit(hufftab[value].byte_code, i);
    bit_buffer_insert_bit(inputbyte, eotbit);
  }

  fprintf(file_2, "%s", bit_buffer_to_byte_array(inputbyte));


  fclose(file_1);
  fclose(file_2);
}
