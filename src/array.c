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
static void recursive_shift_up(dynamic_array_t da, size_t hole_index, size_t curr_index, void *element_to_move);

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

void *da_pop(dynamic_array_t da) {
    if (!da || da->size == 0) {
        return NULL; 
    }

    void *last = (uint8_t *)da->data + (da->size - 1) * da->element_size;
    
    void *element = safe_malloc(da->element_size);
    memcpy(element, last, da->element_size);
    da->size--;

    return element; 
}

void *da_pop_front(dynamic_array_t da) {
    return da_remove_at(da, 0);
}

void *da_remove_at(dynamic_array_t da, ptrdiff_t index) {
    if (!da || da->size == 0) {
        return NULL; 
    }

    ptrdiff_t pos = (index >= 0) ? index : ((ptrdiff_t)da->size + index);
    if (pos < 0 || pos >= (ptrdiff_t)da->size) {
        return NULL;
    }

    void *location = (uint8_t *)da->data + (pos * da->element_size);
    void *element = safe_malloc(da->element_size);
    memcpy(element, location, da->element_size);
    
    recursive_shift_up(da, pos, da->size, NULL);
    da->size--;
    return element; 
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
    if (!da) {
        return NULL;
    }
    
    ptrdiff_t pos = (index >= 0) ? index : ((ptrdiff_t)da->size + index);
    
    if (pos < 0 || pos >= (ptrdiff_t)da->size) {
        return NULL;
    }
    
    void *element_copy = safe_malloc(da->element_size);
    
    memcpy(element_copy, (uint8_t *)da->data + (pos * da->element_size), da->element_size);
    
    return element_copy;
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
 * 
 * @return This function does not return anything
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
 * 
 * @return This function does not return anything
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
 * @return This function does not return anything
 */
static void recursive_shift_down(dynamic_array_t da, size_t index, void *element_to_move) {
    if (index >= da->size) {
        return; 
    }

    void *curr_index = (uint8_t *)da->data + (index * da->element_size);

    uint8_t *temp = safe_malloc(da->element_size);

    memcpy(temp, curr_index, da->element_size); 
    memcpy(curr_index, element_to_move, da->element_size);

    if (index == da->size - 1) {
        free(temp);
        return;
    }

    recursive_shift_down(da, index + 1, temp);
    free(temp);
}

/**
 * @brief Shifts down elements from the right end to the left to fill in a gap
 * 
 * Starting from the rightside end, move each element to the left, until
 * the final move index is reached (this index is the 'hole')
 * 
 * Call this function with curr_index = end_index (index of last element)
 * Call this function with NULL for the element to move (we want it to make null where last elem was)
 * 
 * @param[in,out] da The array to be shift fixed
 * @param[in] hole_index The index of the hole (0-index)
 * @param[in] curr_index The current index the recursion is on (call using end)
 * @param[in] element_to_move The element that is recursively moving left (call using NULL)
 * 
 * @return This function does not return anything
 */
static void recursive_shift_up(dynamic_array_t da, size_t hole_index, size_t curr_index, void *element_to_move) {
    if (curr_index < hole_index) {
        return; 
    }

    void *curr_pos = (uint8_t *)da->data + (curr_index * da->element_size);

    uint8_t *temp = safe_malloc(da->element_size);

    if (element_to_move == NULL) {
        memcpy(temp, curr_pos, da->element_size);
        element_to_move = temp;
    } else {
        memcpy(temp, curr_pos, da->element_size); 
        memcpy(curr_pos, element_to_move, da->element_size);
    }

    if (curr_index == hole_index) {
        memcpy(curr_pos, element_to_move, da->element_size);
        free(temp);
        return;
    }

    recursive_shift_up(da, hole_index, curr_index - 1, temp);
    free(temp);
}