// Thomas Petkovic
// Created 01 February 2025

// Interface to a dynamic array ADT
// - Any data type can be stored within the array


#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct dynamic_array *dynamic_array_t;

dynamic_array_t da_create(size_t element_size, int initial_capacity);
void da_destroy(dynamic_array_t da);
void da_append(dynamic_array_t da, void *element);


// choose the position of element to view, 0 indexed
// if you come from the negative, its from the behind.
// if you go out of bounds, NULL is returned
void *da_view(dynamic_array_t da, int pos);


#endif