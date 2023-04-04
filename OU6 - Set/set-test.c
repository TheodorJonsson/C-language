#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "set.h"

void populate_set(set *s, int mult);
void print_set(set *s);

bool verify_union(const set *s1, const set *s2);
bool verify_intersection(const set *s1, const set *s2);
bool verify_difference(const set *s1, const set *s2);
bool verify_subset(const set *s1, const set *s2);
bool verify_equal_and_remove(void);




int main(void)
{
  srand(time(NULL));
 //Creates two sets to use for the testing
  set *s1 = set_empty();
  set *s2 = set_empty();
  
//populate these sets with values from 0-9 for the first and 0-19 for the second
  populate_set(s1, 1);
  populate_set(s2, 2);
//verifies that the functions work.
  verify_union(s1, s2);
  verify_intersection(s1, s2);
  verify_difference(s1, s2);
  verify_subset(s1, s2);
  verify_equal_and_remove();
//should print out 0,1,2,3,4,5,6,7,8,9 if set_get_values, set_size works
  print_set(s1);

  set_destroy(s1);
  set_destroy(s2);

  return 0;
}
/**
* @brief Populatees the set
*
* Inserts values from 0 up to 10 times mult from the paramter
* using set_insert
*
* @param s, which is the set
* @param mult, what to multiply by 10 how many values to be inserted
*
* @return -
*/
void populate_set(set *s, int mult)
{
  for(int i = 0; i < 10*mult; i++)
  {
    set_insert(i, s);
  }
}

/**
* @brief Prints the set
*
* Creates the array using set_get_values
* then prints the array.
*
* @param s, which is the set
*
* @return -
*/
void print_set(set *s)
{
  int *arr = set_get_values(s);
  for(int i = 0; i < set_size(s); i++)
  {
    printf(" %d ", arr[i]);
  }
  printf("\n");
  free(arr);
}

/**
* @brief verifies that set_union works
*
* Creates a new set using set_union that should be
* the same as s2 because of how s1 and s2 were populated
* then checks if s3 and s2 are equal using set_equal
* returns true, if they are false if they aren't.
*
* @param s1, which is the first set
* @param s2, which is the second set
*
* @return true if works, false if doesnt..
*/
bool verify_union(const set *s1, const set *s2)
{
  printf("set_union.... ");
  // s3 should be the same as s2 because of how we populated s1 and s2
  set *s3 = set_union(s1, s2);
  if(set_equal(s2, s3))
  {
    printf("PASS\n");
    set_destroy(s3);
    return true;
  }
  set_destroy(s3);
  printf("FAIL\n");
  return false;
}

/**
* @brief verifies that set_intersection works
*
* Creates a new set using set_intersection that should be the same
* as s1 because of how s1 and s2 were populated
* then checks if s1 and s3 are equal using set_equal.
*
* @param s1, which is the first set.
* @param s2, which is the second set.
*
* @return true if works, false if doesnt.
*/
bool verify_intersection(const set *s1, const set *s2)
{
  printf("set_intersection.... ");
  // s3  should be the same as s1 because of how we populated s1 and s2.
  set *s3 = set_intersection(s1, s2);
  if(set_equal(s1, s3))
  {
    printf("PASS\n");
    set_destroy(s3);
    return true;
  }
  printf("FAIL\n");

  set_destroy(s3);

  return false;
}

/**
* @brief verifies that set_difference works
*
* Creates a new set using set_difference then creates another set
* then populates the second created set how the set_difference should've
* created the first created set. then checks if they are equals if they are
* returns true, false if they aren't.
*
* @param s1, which is the first set.
* @param s2, which is the second set.
*
* @return true if works, false if doesnt.
*/
bool verify_difference(const set *s1, const set *s2)
{
  printf("set_difference.... ");

  set *s3 = set_difference(s1, s2);
  set *s4 = set_empty();
  for(int i = 10; i < 20; i++)
  {
    set_insert(i, s4);
  }
  //s3 and s4 should be equal if populated correctly
  if(set_equal(s4, s3))
  {
    printf("PASS\n");

    set_destroy(s3);
    set_destroy(s4);

    return true;
  }
  printf("FAIL\n");

  set_destroy(s3);
  set_destroy(s4);

  return false;
}

/**
* @brief verifies that set_subset works
*
* s1 should be a subset of s2 because of how they were populated.
* returns true if s1 is a subset false if it isn't.
*
* @param s1, which is the first set.
* @param s2, which is the second set.
*
* @return true if works, false if doesnt.
*/
bool verify_subset(const set *s1, const set *s2)
{
  printf("set_subset.... ");
  //s1 should be a subset to s2
  if(set_subset(s1, s2))
  {
    printf("PASS\n");
    return true;
  }
  printf("FAIL\n");
  return false;
}

/**
* @brief verifies that set_equal and set_remove works
*
* Creates two new sets and populates them so they should be equal.
* Send them to set_equal as parameters if they arent equals return false.
* then use set_remove on set1 and send both to set_equal now they shouldn't be
* equals and if they are return false.
* if all goes through return true.
*
* @return true if it works, false if it doesn't
*/
bool verify_equal_and_remove(void)
{
  printf("set_equal and set_remove....");
  set *set1 = set_empty();
  set *set2 = set_empty();

  populate_set(set1, 1);
  populate_set(set2, 1);

  if(!(set_equal(set1, set2)))
  {
    printf("FAIL\n");
    return false;
  }
  set_remove(4, set1);
  if(set_equal(set1, set2))
  {
    set_destroy(set1);
    set_destroy(set2);
    printf("FAIL\n");
    return false;
  }
  printf("PASS\n");
  set_destroy(set1);
  set_destroy(set2);
  return true;
}
