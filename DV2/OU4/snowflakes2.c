#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000
struct snowflake
{
  int snowflake[6];
  int value;
};
struct snowflake *fill_snowflakes(int amount_of_flakes);

bool is_equal(struct snowflake *snowflakes, int amount_of_flakes);
bool compare_snowflakes(int snowflake_1[], int snowflake_2[]);

void quicksort(struct snowflake *snowflakes, int lp, int up);
int partition(struct snowflake *snowflakes, int lp, int up);;
void swap(struct snowflake *snowflakes, int lp, int up);

int main(void)
{
   int amount_of_flakes = 0;
   scanf("%d", &amount_of_flakes);
   struct snowflake *snowflakes = fill_snowflakes(amount_of_flakes);
   quicksort(snowflakes, 0, amount_of_flakes - 1);
   printf(is_equal(snowflakes, amount_of_flakes) ? "Twin snowflakes found.\n" : "No two snowflakes are alike.\n");

   return 0;
}


struct snowflake *fill_snowflakes(int amount_of_flakes)
{
   int input;
   struct snowflake *snowflakes = malloc(amount_of_flakes*sizeof(struct snowflake));
   for(int i = 0; i < amount_of_flakes; i++)
   {
     snowflakes[i].value = 0;
   }
   for(int i = 0; i < amount_of_flakes; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         scanf("%d", &input);
         snowflakes[i].snowflake[j] = input;
         snowflakes[i].value = snowflakes[i].value + input;
      }
   }
   return snowflakes;
}


bool is_equal(struct snowflake *snowflakes, int amount_of_flakes)
{
  for(int i = 0; i < amount_of_flakes; i++)
  {
    int j = i;
    while(snowflakes[i].value <= snowflakes[j + 1].value)
    {
      if((snowflakes[i].value == snowflakes[j + 1].value) &&
          compare_snowflakes(snowflakes[i].snowflake, snowflakes[j + 1].snowflake))
      {
        return true;
      }
      j++;
    }
    /*if(snowflakes[i].value < snowflakes[(amount_of_flakes/2) + 1].value)
    {
      int j = 0;
      while(snowflakes[i].value < snowflakes[j].value)
      {
          if((i != j) && (snowflakes[i].value == snowflakes[j].value) &&
          (compare_snowflakes(snowflakes[i].snowflake, snowflakes[j].snowflake)))
          {
            return true;
          }
          j++;
      }
    }
    else
    {
      int j = amount_of_flakes;
      while(snowflakes[i].value >= snowflakes[j].value)
      {
        if((i != j) && (snowflakes[i].value == snowflakes[j].value) &&
        (compare_snowflakes(snowflakes[i].snowflake, snowflakes[j].snowflake)))
        {
          return true;
        }
        j--;
      }
    }*/
  }
  return false;
}


bool compare_snowflakes(int snowflake_1[], int snowflake_2[])
{
   for(int i = 0; i < 6; i++) {

      if((snowflake_1[0] == snowflake_2[i]) &&
         ((snowflake_1[5] == snowflake_2[(i + 1) % 6]) ||
         (snowflake_1[5] == snowflake_2[((i - 1) + 6) % 6]))) {

         return true;
      }
   }

   return false;
}

void quicksort(struct snowflake *snowflakes, int lp, int up)
{
    if(lp < up)
    {
      int dividingline = partition(snowflakes, lp, up);

      quicksort(snowflakes, lp, dividingline - 1);
      quicksort(snowflakes, dividingline + 1, up);
    }
}

int partition(struct snowflake *snowflakes, int lp, int up)
{
  int bound = snowflakes[up].value;
  int i = (lp - 1);

  for(int j = lp; j <= up - 1; j++)
  {
    if(snowflakes[j].value < bound)
    {
      i++;
      swap(snowflakes, i, j);
    }
  }
  swap(snowflakes, i + 1, up);

  return i + 1;
}

void swap(struct snowflake *snowflakes, int lp, int up)
{
  struct snowflake temp;
  temp = snowflakes[lp];
  snowflakes[lp] = snowflakes[up];
  snowflakes[up] = temp;
}
