#include <stdio.h>
#include <stdbool.h>
#include "table.h"

static void populate_table(Table *tab);
static bool verify_table_presence(Table *tab);
static bool verify_table_absence(Table *tab);



int main(void)
{
    // Create an empty table.
    Table *tab = table_create(100);

    populate_table(tab);

    printf("Test the presence of added key/value pairs ... ");
    if(verify_table_presence(tab))
    {
      printf("PASS\n");
    }
    else
    {
      printf("FAIL\n");
    }

    printf("Test the absence of non-added keys ... ");
    if(verify_table_absence(tab))
    {
      printf("PASS\n");
    }
    else
    {
      printf("FAIL\n");
    }
    // Clean up.
    table_destroy(tab);

    return 0;
}
/**
*  populates the table
*
* populates the table with two for loops
* and uses the function table_insert to
* insert the values in the for loop
*
* param *tab, a pointer to the table
*
* return -
*/
static void populate_table(Table *tab)
{
  // Insert the key/value pairs (n, -n) for n = 1, 2, ..., 10.
  for (int n = 1; n <= 10; n++)
  {
    table_insert(tab, n, -n);
  }

  // Insert the key/value pairs (n, -n) for n = 101, 102, ..., 110.
  for (int n = 101; n <= 110; n++)
  {
    table_insert(tab, n, -n);
  }
}
/**
* verifies
*
* checks if the table has been populated
* in the correct positions with the correct value
*
* param *tab, pointer to a table
* returns true or false
*/
static bool verify_table_presence(Table *tab)
{
  for(int n = 1; n <= 10; n++)
  {
    int value;
    int key = n;
    if(!(table_lookup(tab, key, &value) && -key == value))
    {
      return false;
    }
  }
  for(int n = 101; n <= 110; n++)
  {
    int value;
    int key = n;
    if(!(table_lookup(tab, key, &value) && -key == value))
    {
      return false;
    }
  }
  return true;
}
/**
* verifies the table
*
* checks if the table hasn't been populated
* in the other positions
*
* param *tab, pointer to a table
* returns true or false
*/
static bool verify_table_absence(Table *tab)
{
  for(int n = 1; n <= 200; n++)
  {
    int value;
    int key = n;
    if(!(n >= 1 && n <= 10))
    {
      if(!(n >= 101 && n <= 110))
      {
        if(table_lookup(tab, key, &value))
        {
          return false;
        }
      }
    }
  }
  return true;
}
