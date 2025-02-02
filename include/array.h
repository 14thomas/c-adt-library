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
 * @brief Appends an element to the front of the array
 * 
 * Appends a copy of the data pointed to by `element` to the front the array.
 * If the array is at capacity, its storage will be automatically resized.
 * 
 * @param[out] da A dynamic array
 * @param[in] element A pointer to the data to be appended. This function 
 * copies exactly `element_size` bytes from this pointer into the array.
 * 
 * @return This function does not return anything
 */
void da_prepend(dynamic_array_t da, void *element);

/**
 * @brief Inserts an element at a specific position, shifting subsequent
 * elements
 * 
 * @param[in,out] da A dynamic array. If NULL is passed in, nothing occurs
 * @param[in] index The index of where the new element is positioned
 * @param[in] element A pointer to the new element
 * 
 * @returns This function does not return anything 
 */
void da_insert(dynamic_array_t da, size_t index, void *element);

/**
 * @brief Removes and returns the last element
 * 
 * The function removes the last element from the dynamic array and returns
 * a pointer to a copy of that element. The copy is on the heap, and must
 * be freed when by the caller.
 * 
 * @param[in,out] da A dynamic array. If NULL is passed in, NULL returned
 * 
 * @returns A pointer to the element at last position. NULL returned if NULL
 * is passed in
 */
void *da_pop(dynamic_array_t da);

/**
 * @brief Removes and returns the first element
 * 
 * The function removes the first element from the dynamic array and returns
 * a pointer to a copy of that element. The copy is on the heap, and must
 * be freed when by the caller.
 * 
 * @param[in,out] da A dynamic array. If NULL is passed in, NULL returned
 * 
 * @returns A pointer to the element at first position. NULL returned if NULL
 * is passed in
 */
void *da_pop_front(dynamic_array_t da);

/**
 * @brief Removes and returns the element at a given position in the array
 * 
 * The function removes an element from the dynamic array and returns
 * a pointer to a copy of that element. The copy is on the heap, and must
 * be freed when by the caller.
 * 
 *  The position `index` may be:
 * 
 * - A non-negative index (0-based from front)
 * 
 * - Negative index (from the back, -1 refers to last element)
 * 
 * @param[in,out] da A dynamic array. If NULL is passed in, NULL returned
 * @param[in] index The index of the element. Negative value counts from
 * the end.
 * 
 * @returns A pointer to the element at the specified position, or `NULL` if 
 * `pos` is out of bounds or if `da` is NULL.
 */
void *da_remove_at(dynamic_array_t da, ptrdiff_t index);

/**
 * @brief Returns a pointer to the element at a given position in the array
 * 
 * This function allocates memory for a new copy of the element at position.
 * This ensures that if the element is later modified / removed from array, 
 * the copy remains valid. Ensure the memory is freed when not in use.
 * 
 * The position `index` may be:
 * 
 * - A non-negative index (0-based from front)
 * 
 * - Negative index (from the back, -1 refers to last element)
 * 
 * @param[in] da A dynamic array
 * @param[in] index The index of the element. Negative value counts from
 * the end
 * 
 * @return A pointer to the element at the specified position, or `NULL` if 
 * `pos` is out of bounds or if `da` is invalid. 
 */
void *da_get(dynamic_array_t da, ptrdiff_t index);

/**
 * @brief Returns the amount of elements stored in the array
 * 
 * @param[in] da A dynamic array
 * 
 * @return The amount of elements stored in the array. If NULL is passed in,
 * then returns 0.
 */
size_t da_size(dynamic_array_t da);

/**
 * @brief Returns a boolean indicating whether the array is empty
 * 
 * @param[in] da A dynamic array
 * 
 * @return true if the array is empty, false otherwise. Also returns true
 * if NULL is passed in.
 */
bool da_is_empty(dynamic_array_t da);

#endif