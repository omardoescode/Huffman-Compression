#include <stdint.h>
#include <wchar.h>
#ifndef VECTOR_HEADER
#define VECTOR_HEADER
#define MINIMUM_CAPACITY 10
#define v_type size_t

typedef struct vector vector;

/**
 * @brief Construct a vector (expandable array)
 *
 * Construct the vector with max(initial_capacity, MINIMUM_CAPACITY)
 * @param initial_capacity the proposed capacity for the vector
 * @return A pointer to the vector
 */
vector *v_init(size_t initial_capacity);

/**
 * @brief Getter for capacity
 *
 * Retrieve the capacity of the given vector
 *
 * @param v A pointer to the vector
 * @return The capacity of the vector
 */
const size_t v_capacity(const vector *v);

/**
 * @brief Getter for size
 *
 * Retrieve the size of the given vector
 *
 * @param v A pointer to the vector
 * @return The size of the vector
 */
const size_t v_size(const vector *v);

/**
 * @brief Getter for elements in the vector
 *
 * Retrieve the element at the given index
 * @param v A pointer to the vector
 * @param i the index
 * @return A pointer to the element retrieved
 */
v_type *v_get(const vector *v, size_t index);

/**
 * @brief Copy vector from source to destination
 *
 * Free the destination vector if needed then copy all the values, size and
 * capacity
 */
void v_copy(vector **dest, const vector *src);

/**
 * @brief Add an element to the vector
 *
 * Expand the vector if needed, then add the element to the end of the list
 *
 * @param v The vector to append the element to
 * @param val The element to be appended
 */
void v_append(vector *v, v_type val);

/**
 * @brief Set an element at the given index
 *
 * Expand the vector if needed, than set the element at the given index
 *
 * @param v A pointer to the vector to insert the element to
 * @param index The index to change
 * @param val The value to insert
 */
void v_set(vector *v, size_t index, v_type val);

/**
 * @brief free the vector
 *
 * Free the values first, then the vector (struct)
 *
 * @param v The vector to free
 */
void v_free(vector *v);
#endif
