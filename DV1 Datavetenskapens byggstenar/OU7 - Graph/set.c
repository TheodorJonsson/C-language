#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "set.h"

struct set {
    int capacity;
    int size;
    char *array;
};

set *set_empty()
{
  set *set = malloc(sizeof(struct set));

  set->capacity = 8;
  set->size = 0;
  set->array = calloc(8, sizeof(set->array));

  return set;
}


set *set_single(const int value)
{
  set *set = set_empty();

  set_insert(value, set);

  return set;
}


void set_insert(const int value, set *s)
{
    if (!set_member_of(value, s))
    {
        int bit_in_array = value;


        if (bit_in_array >= s->capacity)
        {
            int no_of_bytes = bit_in_array / 8 + 1;
            s->array = realloc(s->array, no_of_bytes);
            for (int i = s->capacity / 8 ; i < no_of_bytes ; i++)
            {
                s->array[i] = 0;
            }
            s->capacity = no_of_bytes * 8;
        }


        int byte_no = bit_in_array / 8;
        int bit = 7 - bit_in_array % 8;
        s->array[byte_no] = s->array[byte_no] | 1 << bit;
        s->size++;
    }
}


// Note: More effective implementations are possible, but this is
// okay for this assignment.
set *set_union(const set *const s1, const set *const s2)
{
    set *s = set_empty();

    for (int i = 0 ; i < s1->capacity || i < s2->capacity ; i++)
    {
        if (set_member_of(i, s1) || set_member_of(i, s2))
        {
            set_insert(i, s);
        }
    }

    return s;
}


set *set_intersection(const set *const s1, const set *const s2)
{
  set *s = set_empty();

    for (int i = 0 ; i < s1->capacity || i < s2->capacity ; i++)
    {
        if (set_member_of(i, s1) && set_member_of(i, s2))
        {
            set_insert(i, s);
        }
    }

    return s;
}

set *set_difference(const set *const s1, const set *const s2)
{
  set *s = set_empty();

    for (int i = 0 ; i < s1->capacity || i < s2->capacity ; i++)
    {
        if (set_member_of(i, s1) != set_member_of(i, s2))
        {
            set_insert(i, s);
        }
    }

    return s;
}


bool set_is_empty(const set *const s)
{
  if(s->size <= 0)
  {
    return true;
  }
  return false;
}


bool set_member_of(const int value, const set *const s)
{
    int bit_in_array = value; // To make the code easier to read

    if (bit_in_array >= s->capacity) {
        return false;
    }

    int byte_no = bit_in_array / 8;
    int bit = 7 - bit_in_array % 8;
    char the_byte = s->array[byte_no];

    return the_byte & 1 << bit;
}


int set_choose(const set *const s)
{
  for(int i = 0; i < s->capacity; i++)
  {
    int rnd = rand() % ((s->capacity - 0) + 1);
    if(set_member_of(rnd, s))
    {
      return rnd;
    }
  }
  return 0;
}


void set_remove(const int value, set *const s)
{
  if(set_member_of(value,s))
  {
    bool byte_found = false;
    int total_byte_s = s->capacity/8;

    for (int num_byte = 0; num_byte < total_byte_s; num_byte++)
    {
      int max_byte = num_byte * 8 + 7;

      if(max_byte >= value && !byte_found)
      {
        int bit = 7 - value % 8;
        int bit_remove = 1 << bit;

        s->array[num_byte] = s->array[num_byte] ^ bit_remove;
        byte_found = true;
        s->size--;
      }
    }
  }
}


bool set_equal(const set *const s1, const set *const s2)
{
   for (int i = 0 ; i < s1->capacity && i < s2->capacity ; i++)
   {
        if (set_member_of(i, s1) != set_member_of(i, s2))
        {
          return false;
        }
    }
    return true;
}


bool set_subset(const set *const s1, const set *const s2)
{
  for (int i = 0 ; i < s1->size ; i++)
    {
      if (set_member_of(i, s1) != set_member_of(i, s2))
        {
          return false;
        }
    }
    return true;
}

int set_size(const set *const s)
{
  return s->size;
}

int *set_get_values(const set *const s)
{
  int *arr = malloc(s->size*sizeof(int));
  int j = 0;
  for(int i = 0; i < s->capacity; i++)
  {
    if(set_member_of(i, s))
    {
      arr[j] = i;
      j++;
    }
  }
  return arr;
}

void set_destroy(set *s)
{
  free(s->array);
  free(s);
}
