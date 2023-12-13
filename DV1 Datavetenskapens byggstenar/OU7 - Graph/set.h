#ifndef SET_H
#define SET_H

#include <stdbool.h>
/**
 * @defgroup set my Set
 *
 * @brief Specification of the datatype Set as a bitvector
 *
 * Lets the user create a set and store the values as bits.
 * lets the user insert values, get the union of two sets,
 * get the intersetion of two sets get the difference of two sets,
 * check if a set is a subset of another set and get the values as a array.
 *
 *
 * @author Theodor Jonsson
 * @{
 */


/**
* @brief the type for a set
*
* Set which holds:
*
* capacity, a integer that is the current max size of the set
*
* size, a integer that is the current size of the set
*
* array, which is a char array that holds the values
*/

typedef struct set set;

/**
* @brief Creates a new empty set
*
* Creates a new empty set and allocates the memory for the set.
* assign the capacity to 8 i.e. a byte and assign the size as 0.
* allocates the memory for the char array.
*
*
* @return set, the newly created set
*/
set *set_empty();


/**
* @brief creaetes a new set with a single member
*
* Calls on set_empty to create a new empty set
* then calls on set_insert to insert the value from the parameter
*
* @param value, which is the value to be inserted
*
* @return set, the newly created set with a single member
*/
set *set_single(const int value);


/**
* @brief Insert the value in the set
*
* Checks if the valuee has already been inserted if it has nothing happens,
* if not checks if the max capacity has been reached if it has allocates the
* memory for it and sets the newly created spaces in the array to 0.
*
* Then sets the bit from the value and inserts the bitvalue in to the array
*
* @param value, which is the value to be inserted
* @param s, which is the set to be inserted in
*
* @return -
*/
void set_insert(const int value, set *s);


/**
* @brief Returns a new set that is the union of the two sets
*
* Creates a new set with set_empty
* Then goes through the sets from the parameters and checks if the values
* are a member of either set and if it is inserts it to the new set
*
* @param s1, which is the first set
* @param s2, which is the second set
*
* @return s, the union of the sets from the parameters
*/
set *set_union(const set *const s1, const set *const s2);


/**
* @brief Returns a new set that is the intersection of the two sets.
*
* Creates a new set with set_empty.
* Then goes through thee sets from the parameter and checks if the values
* are a member of both the sets if it is inserts it to the new set
*
* @param s1, which is the first set
* @param s2, which is the second set
*
* @return s, the intersection of the sets from the parameter
*/
set *set_intersection(const set *const s1, const set *const s2);


/**
* @brief Returns a new set that is the difference of the two sets (s1 \ s2).
*
* Creates a new set with set_empty.
* Then goes through thee sets from the parameter and checks if the values
* are a member one set but not the other if it is inserts it to the new set
*
* @param s1, which is the first set
* @param s2, which is the second set
*
* @return s, the difference of the sets from the parameter
*/
set *set_difference(const set *const s1, const set *const s2);


/**
* @brief Checks if the set is empty.
*
* Checks if the size of the set is 0 or less and if it is returns true
* and if the size is greater than 0 then returns false
*
* @param s, which is the set to be checked
*
* @return true if it's empty false if it's not
*/
bool set_is_empty(const set *const s);


/**
* @brief Checks if the value is a member of the set.
*
* Checks if the value is greater than the capacity of the set
* if it is returns false.
* gets the byte and bit of the value
* returns the byte bitshifted by the amount of the bit
*
* @param value, which is the value to be checked
* @param s, which is the set
*
* @return false or the byte bitshifted by the amount of the bit.
*/
bool set_member_of(const int value, const set *const s);

/**
* @brief Returns a random member of the set
*
* Goes through the set and gets a random number
* from 0 to the capacity of the set and checks if thee random number
* is apart of the set if it is returns the random number
* if it can't find a number returns 0.
*
* There is a small chance if the capacity is larger than the size of the set
* that the random number generator will only get numbers that isn't apart of
* the set and returns 0 even though there are members of the set.
* @param s, which is the set
*
* @return rnd if it can find a number in the set, 0 if it can't
*/
int set_choose(const set *const s);


/**
* @brief Removes the value from the set.
*
* Checks if the value is a member of the set if it is
* gets the byte and bit of the value to find the right position in the Array
* and then removes the value from the set
*
* @param value, which is the value to be removed
* @param s, which is the set
*
* @return -
*/
void set_remove(const int value, set *const s);


/**
* @brief Checks if the two sets are equal.
*
* Goes through the sets to see if both has the same members
* if they do then returns true if they dont returns false.
*
* @param s1, which is the first set.
* @param s2, which is the second set.
*
* @return true, if they are the same. false, if they aren't the same.
*/
bool set_equal(const set *const s1, const set *const s2);


/**
* @brief Checks if the first set is a subset of the second set.
*
* Goes through the first set to check if it has the same members
* as the second set if it does then returns true, if it doesnt
*
* @param s1, which is the first set.
* @param s2, which is the second set.
*
* @return true, if s1 is a subset of the second, false if it isn't.
*/
bool set_subset(const set *const s1, const set *const s2);


/**
* @brief Returns an array with all the values in the set.
*
* Creates a int array and allocate it to the size of the sets size.
* goes through the set and checks if every value is a member of the set
* if they are they get assigned to the array in order.
*
* the user is responsible for deallocating the array.

* @param s, which is the set.
*
* @return arr, which is the array with the values from the set
*/
int *set_get_values(const set *const s);


/**
* @brief Returns the number of elements in the set.
*
*
* @param s, which is the set
*
* @return the size of the array.
*/
int set_size(const set *const s);


/**
* @brief Destroys the set.
*
* First deallocates the array of the set.
* Then deallocates the set
* @param s, which is the set
*
* @return -
*/
void set_destroy(set *s);
/**
 * @}
 */

#endif /* SET_H */
