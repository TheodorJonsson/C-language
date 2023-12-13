#include <stdio.h>
#include "table.h"


int main(void)
{
    // Create an empty table.
    Table *tab = table_create(100);

    // Insert the key/value pairs (n, -n) for n = 1, 2, ..., 10.
    for (int n = 1; n <= 10; n++) {
        table_insert(tab, n, -n);
    }

    // Insert the key/value pairs (n, -n) for n = 101, 102, ..., 110.
    for (int n = 101; n <= 110; n++) {
        table_insert(tab, n, -n);
    }

    // Lookup the keys n = 1, 2, ..., 200.
    for (int n = 1; n <= 200; n++) {
        int value;
        int key = n;
        if (table_lookup(tab, key, &value)) {
            printf("key %d has value %d\n", key, value);
        } else {
            printf("key %d not present\n", key);
        }
    }

    // Clean up.
    table_destroy(tab);

    return 0;
}
