#include <stdlib.h>
#include "table.h"


Table *table_create(int capacity)
{
    Table *tab = malloc(sizeof(Table));
    tab->capacity = capacity;
    tab->buckets = calloc(tab->capacity, sizeof(struct bucket));
    return tab;
}


void table_destroy(Table *tab)
{
    free(tab->buckets);
    free(tab);
}


static struct bucket *find_bucket(Table *tab, int key)
{
    int hash = key % tab->capacity;
    for (int offset = 0; offset < tab->capacity; offset++)
    {
        struct bucket *b = &tab->buckets[(hash + offset) % tab->capacity];
        if (!b->used || b->key == key)
        {
            return b;
        }
    }
    return NULL;
}


bool table_lookup(Table *tab, int key, int *value)
{
    struct bucket *b = find_bucket(tab, key);
    if (b != NULL && b->used) {
        *value = b->value;
        return true;
    } else {
        return false;
    }
}


void table_insert(Table *tab, int key, int value)
{
    struct bucket *b = find_bucket(tab, key);
    if (b) {
        b->used = true;
        b->key = key;
        b->value = value;
    }
}
