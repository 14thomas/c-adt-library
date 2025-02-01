#include "array.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t

struct dynamic_array {
    void *data;     
    size_t element_size;
    size_t size; // amount of elements currently filled
    size_t capacity; // maximum of elements in this array
};
 
static void *safe_malloc(size_t size);
static void increase_capacity(dynamic_array_t da);
static void ensure_valid_capacity(dynamic_array_t da);

dynamic_array_t da_create(size_t element_size, int initial_capacity) {
    struct dynamic_array *new_array = safe_malloc(sizeof(struct dynamic_array));

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

// adds an element to the end of the array, resizes if required
void da_append(dynamic_array_t da, void *element) {
    // ensure a valid da is provided
    if (!da) {
        return;
    }

    ensure_valid_capacity(da);
    void *destination = (uint8_t *)da->data + (da->size * da->element_size);
    memcpy(destination, element, da->element_size);
}

void *da_view(dynamic_array_t da, int pos) {
    // ensure a valid da is provided
    if (!da) {
        return NULL;
    }
    
    // exclude when we are out of bounds
    if (pos + 1 > da->size || pos < - da->size) {
        return NULL;
    }

    void *destination;
    if (pos >= 0) {
        destination = (uint8_t *)da->data + (pos * da->element_size);
    } else {
        pos *= -1;
        void *last_elem = (uint8_t *)da->data + (da->size * da->element_size);
        destination = last_elem - (pos * da->element_size);
    }
    return destination;
}



static void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
    }
    return ptr;
}

static void increase_capacity(dynamic_array_t da) {
    size_t new_capacity = da->capacity * 2;

    void *new_data = realloc(da->data, da->element_size * new_capacity);
    if (!new_data) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
    }
    
    safe_malloc(new_capacity);

    da->data = new_data;
    da->capacity = new_capacity;
}

// checks the capacity when a new element is to be added
// hence if there is n-1 / n filled, we are fine
// but if we are at n/n then we will resize
static void ensure_valid_capacity(dynamic_array_t da) {
    if (da->data >= da->capacity) {
        increase_capacity(da);
    }
}