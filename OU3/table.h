#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>
/**
 * @defgroup Table my table
 *
 * @brief Specification of a table
 *
 * Lets the user create a table and input values.
 * Stores these values using closed hashing and linaer probing
 * so that if two keys hashes to the same position is resolved by
 * placing the last hashed to the next free location.
 *
 * @{
 */

// The type for a bucket.
/**
* @brief The type for a bucket
*
* key, used to find the right hash
*
* value, the desired value to store in the table
*
* used, is a bool to check if the bucket is used or not
*
*/
struct bucket
{
    int key;
    int value;
    bool used;
};

// The type for the table.
/**
* @brief The type for the table.
*
* capacity, the number of buckets.
*
* *buckets, the bucket array.
*
*/
typedef struct table
{
    // The number of buckets.
    int capacity;
    // The bucket array.
    struct bucket *buckets;
} Table;

// Create an empty table.
/**
* @brief Creates a table and allocates the memory for it
*
* Creates a new table and allocates the memory for it.
* then assigns the capacity of the table from the paramater
* allocates the array for buckets
*
* @param capacity, the desired size of the table
*
* @return tab, the newly created table
*
*/
Table *table_create(int capacity);


/**
* @brief Deallocates the table
*
* Deallocates first the tables buckets,
* then deallocates the table both using free();
*
* @param tab, pointer to a table
*
* @return -
*/
void table_destroy(Table *tab);

// Lookup the value for a key and return false if the key is not found.
/**
* @brief Looks up a value in the table
*
* Creates a new bucket using internal function
* to check if its occupied. If its occupied then it assigns
* the buckets value to the paramaters value and returns the bool true.
* If its not occupied then it returns false
*
* @param tab, pointer to a table
* @param key, the key to the bucket
* @param *value, a pointer to an int
*
* @return true of false
*/
bool table_lookup(Table *tab, int key, int *value);

// Insert a key/value pair and overwrite the value if the key exists.
/**
* @brief Insert a value in to the table.
*
* Creates a new bucket using internal function
* with the table and key from the paramater,
* aswell as create the hash and checks if its full or not.
* Returns either NULL or the bucket.
* After this assigns the key and value to the bucket.
* And sets the bool b.used to true.
*
* @param tab, pointer to a table.
* @param key, the key to the bucket.
* @param value, integer that user wants to insert.
*
*
*/
void table_insert(Table *tab, int key, int value);

/**
* @}
*/

#endif /* TABLE_H */
