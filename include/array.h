// Thomas Petkovic
// Created 01 February 2025

// Interface to a dynamic array ADT
// - Any data type can be stored within the array


#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct dynamic_array *dynamic_array_t;

/**
 * @brief Creates a new dynamic array
 * 
 * @param[in] element_size The size of the elements to be stored in the array
 * @param[in] initial_capacity The initial size of the array to be made
 * 
 * @return The array with respective element size and capacity
 */
dynamic_array_t da_create(size_t element_size, size_t initial_capacity);

/**
 * @brief Destroys a given dynamic array. 
 * 
 * Only frees the memory relating to the array, does not free memory for 
 * individual elements if they themselves are dynamically allocated.
 * 
 * @param[in,out] da A dynamic array
 * 
 * @return This function does not return anything
 */
void da_destroy(dynamic_array_t da);

/** 
 * @brief Appends an element to the end of the array
 * 
 * Appends a copy of the data pointed to by `element` to the end of the array.
 * If the array is at capacity, its storage will be automatically resized.
 * 
 * @param[out] da A dynamic array
 * @param[in] element A pointer to the data to be appended. This function 
 * copies exactly `element_size` bytes from this pointer into the array.
 * 
 * @return This function does not return anything
 */
void da_append(dynamic_array_t da, void *element);

/**
 * @brief Returns a pointer to the element at a given position in the array
 * 
 * The position `pos` may be:
 * 
 * - A non-negative index (0-based from front)
 * 
 * - Negative index (from the back, -1 refers to last element)
 * 
 * @param[in] da A dynamic array
 * @param[in] pos The position of the element. Negative value counts from
 * the end
 * 
 * @return A pointer to the element at the specified position, or `NULL` if 
 * `pos` is out of bounds or if `da` is invalid.
 */
void *da_get(dynamic_array_t da, ptrdiff_t pos);


#endif