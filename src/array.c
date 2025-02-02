#include "array.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // for uint8_t
#include <string.h>

struct dynamic_array {
    void *data;     
    size_t element_size;
    size_t size; // amount of elements currently filled
    size_t capacity; // maximum of elements in this array
};
 
static void *safe_malloc(size_t size);
static void increase_capacity(dynamic_array_t da);
static void ensure_valid_capacity(dynamic_array_t da);
static void recursive_shift_down(dynamic_array_t da, size_t index, void *element_to_move);

dynamic_array_t da_create(size_t element_size, size_t initial_capacity) {
    if (initial_capacity <= 0) {
        return NULL;
    }

    dynamic_array_t new_array = safe_malloc(sizeof(struct dynamic_array));

    new_array->element_size = element_size;
    new_array->size = 0;
    new_array->capacity = initial_capacity;
    
    new_array->data = safe_malloc(initial_capacity * element_size);
    
    return new_array;
}

void da_destroy(dynamic_array_t da) {
    // ensure a valid da is provided
    if (da) {
        free(da->data);
        free(da);
    }
}

void da_append(dynamic_array_t da, void *element) {
    // ensure a valid da is provided
    if (!da) {
        return;
    }

    ensure_valid_capacity(da);
    void *destination = (uint8_t *)da->data + (da->size * da->element_size);
    memcpy(destination, element, da->element_size);
    da->size++;
}

void da_prepend(dynamic_array_t da, void *element) {
    // ensure a valid da is provided
    if (!da) {
        return;
    }
    da_insert(da, 0, element);
}


void da_insert(dynamic_array_t da, size_t index, void *element) {
    // ensure a valid da is provided
    if (!da) {
        return;
    }
    ensure_valid_capacity(da);
    recursive_shift_down(da, index, da_get(da, index));

    void *destination = (uint8_t *)da->data + (index * da->element_size);
    memcpy(destination, element, da->element_size);
    da->size++;
}

void *da_get(dynamic_array_t da, ptrdiff_t index) {
    // ensure a valid da is provided
    if (!da) {
        return NULL;
    }
    
    ptrdiff_t pos = (index >= 0) ? index : ((ptrdiff_t)da->size + index);

    // check for out of bounds
    if (index < 0 || index >= (ptrdiff_t)da->size) {
        return NULL;
    }

    return (uint8_t *)da->data + (pos * da->element_size);
}

size_t da_size(dynamic_array_t da) {
    if (!da) {
        return 0;
    }
    return da->size;
}

bool da_is_empty(dynamic_array_t da) {
    return !da || da->size == 0;
}

/**
 * @brief Allocates memory with failure checking
 * 
 * Attempts to allocate `size` bytes. If the allocation fails, prints error 
 * message and terminates the program.
 * 
 * @param[in] size Number of bytes to allocate
 * 
 * @return A pointer to the allocated memory
 */
static void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
    }
    return ptr;
}

/**
 * @brief Doubles the capacity of the dynamic array
 * 
 * Reallocates the internal data of the array to twice its current capacity.
 * 
 * @param[in,out] da The dynamic array whose capacity will be increased. Must
 * not be NULL.
 */
static void increase_capacity(dynamic_array_t da) {
    size_t new_capacity = da->capacity * 2;


    void *new_data = realloc(da->data, da->element_size * new_capacity);
    if (!new_data) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
    }

    da->data = new_data;
    da->capacity = new_capacity;
}

/**
 * @brief Ensures the dynamic array has enough capacity for a new element
 * 
 * If there is not enough capacity for a new element, 
 * calls `increase_capacity()` to double the capacity.abort
 * 
 * If there is 1 space left, a resize will not occur.
 * 
 * @param[in,out] da The dynamic array to check and possibly expand. 
 * Must not be NULL.
 */
static void ensure_valid_capacity(dynamic_array_t da) {
    if (da->size >= da->capacity) {
        increase_capacity(da);
    }
}

/**
 * @brief Shifts down the position of each element starting from `index`
 * 
 * `element_to_move` should be the element at `index` position.
 * 
 * @param[out] da The dynamic array for which elements are shifted
 * @param[in] index The position for which the shifting shall start from
 * @param[in,out] element_to_move The element currently at `index`, which
 * shall be moved to the right
 * 
 */
static void recursive_shift_down(dynamic_array_t da, size_t index, void *element_to_move) {
    if (index >= da->size) {
        void *last_index = (uint8_t *)da->data + (index * da->element_size);
        memcpy(last_index, element_to_move, da->element_size);
        return;
    }

    void *curr_index = (uint8_t *)da->data + (index * da->element_size);

    uint8_t temp[da->element_size];
    memcpy(temp, curr_index, da->element_size);
    memcpy(curr_index, element_to_move, da->element_size);

    recursive_shift_down(da, index + 1, temp);
}