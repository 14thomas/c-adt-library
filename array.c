#include "array.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> // for size_t



struct dynamic_array {
    void *data;     
    size_t element_size;
    size_t size; // amount of elements currently filled
    size_t capacity; // maximum of elements in this array
};
 
dynamic_array_t da_create(size_t element_size, int initial_capacity) {
    struct dynamic_array *new_array = safe_malloc(sizeof(struct dynamic_array));

    new_array->element_size = element_size;
    new_array->size = 0;
    new_array->capacity = initial_capacity;
    
    new_array->data = safe_malloc(initial_capacity * element_size);
}

static void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
    }
    return ptr;
}

