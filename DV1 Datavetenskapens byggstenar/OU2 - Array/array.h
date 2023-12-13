#ifndef ARRAY_H
#define ARRAY_H
/**
 * @defgroup array my array
 *
 * @brief Specification of an array
 *
 * Lets the user create a 2D array that is
 * dynamically stored as a one dimensionall array.
 * Also lets the user input values and get those values aswell
 *
 *
 * @{
 */

/**
 * @brief The type for a 2D array.
 *
 * n1 amount of rows
 * n2 amount of columns
 * *data pointer to an int which will hold the data
 * @return
 */
typedef struct array
{
    int n1;
    int n2;
    int *data;
} Array;

// Create and return a zero array of size n1 rows by n2 columns.
/**
 * @brief creates and return a zero array of size n1 rows by n2 columns.
 *
 * Creates and Array and allocates the memory for it.
 * Assigns the values of n1 and n2 from the paramater
 * to the newly created arrays n1 and n2.
 * Allocates the memory for and array the size of n1*n2
 * and sets all the values to 0
 *
 * @param int n1, the size of rows
 * @param int n2, the size of columns
 *
 * @return arr, the newly created array
 */
Array *array_create(int n1, int n2);

// Destroy an array.
/**
 * @brief Destroy an array.
 *
 * frees the memory of the data in the array
 * then frees the array
 * @param Array arr
 *
 * @return -
 */
void array_destroy(Array *arr);

// Get the number of rows.
/**
 * @brief Get the number of rows.
 *
 * @param arr, which is a pointer to an array
 *
 * @return rows, the amount of rows
 */
int array_rows(const Array *arr);

// Get the number of columns.
/**
 * @brief Get the number of columns.
 *
 * gets the amount of columns in the array
 *
 * @param arr, which is a pointer to an array
 *
 * @return columns, the amount of columns
 */
int array_columns(const Array *arr);

// Return the value at row i1 and column i2 (zero-based indexing).
/**
 * @brief Return the value at row i1 and column i2
 *
 *
 * @param arr, which is a pointer to an array
 *
 * @return value
 */
int array_get(const Array *arr, int i1, int i2);

// Set the value at row i1 and column i2 (zero-based indexing).
/**
 * @brief Set the value at row i1 and column i2
 *
 * @param arr, which is a pointer to an array
 *
 * @return value
 */
void array_set(Array *arr, int i1, int i2, int value);

/**
 * @}
 */
#endif /* ARRAY_H */
