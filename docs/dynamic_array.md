# 📖 Dynamic Array Function Reference (`adt_array.h`)

This document provides a detailed reference for all functions available in the **Dynamic Array** ADT.

---

## 1️⃣ Creation and Destruction

### 🔹 Initialization  
- `dynamic_array_t da_create(size_t element_size, size_t initial_capacity)`:  
  _Creates a new dynamic array with an initial capacity._  

### 🔹 Cleanup  
- `void da_destroy(dynamic_array_t da)`:  
  _Frees allocated memory and cleans up resources._  
- `da_clear(dynamic_array_t da)`:  
  _Removes all elements but retains allocated memory for reuse._ _(Coming Soon) 🚀_ 

---

## 2️⃣ Insertion Operations

### 🔹 Appending and Prepending  
- `void da_append(dynamic_array_t da, void *element)`:  
  _Adds an item to the end of the array._  
- `void da_prepend(dynamic_array_t da, void *element)`:  
  _Adds an item to the beginning of the array._ 

### 🔹 Inserting at Specific Positions  
- `void da_insert(dynamic_array_t da, size_t index, void *element)`:  
  _Inserts an element at a specific position, shifting subsequent elements._ 
- `da_insert_multiple(dynamic_array_t da, size_t index, void *elements, size_t count)`:  
  _Inserts multiple elements starting at a given index._ _(Coming Soon) 🚀_

---

## 3️⃣ Deletion and Removal Operations  

### 🔹 Removing from Ends  
- `da_pop(dynamic_array_t da)`:  
  _Removes and returns the last element._ 
- `da_pop_front(dynamic_array_t da)`:  
  _Removes and returns the first element._ _(Coming Soon) 🚀_

### 🔹 Removing from Specific Positions  
- `da_remove_at(dynamic_array_t da, size_t index)`:  
  _Removes the element at a given index._ _(Coming Soon) 🚀_ 
- `da_remove_range(dynamic_array_t da, size_t start_index, size_t count)`:  
  _Removes a range of elements starting at a specified index._ _(Coming Soon) 🚀_

### 🔹 Removing by Value  
- `da_remove(dynamic_array_t da, void *element)`:  
  _Removes the first occurrence of a specified element._ _(Coming Soon) 🚀_
- `da_remove_all(dynamic_array_t da, void *element)`:  
  _Removes all occurrences of a specified element._ _(Coming Soon) 🚀_

---

## 4️⃣ Element Access and Modification  

### 🔹 Direct Access  
- `void *da_get(dynamic_array_t da, size_t index)`:  
  _Retrieves the element at a specified index._ 
- `da_set(dynamic_array_t da, size_t index, void *element)`:  
  _Replaces the element at a specified index._ _(Coming Soon) 🚀_  

### 🔹 Convenience Accessors  
- `da_front(dynamic_array_t da)`:  
  _Returns the first element._ _(Coming Soon) 🚀_
- `da_back(dynamic_array_t da)`:  
  _Returns the last element._ _(Coming Soon) 🚀_
- `da_at(dynamic_array_t da, size_t index)`:  
  _Retrieves the element at an index with bounds checking._ _(Coming Soon) 🚀_ 

### 🔹 Search Functions  
- `da_index_of(dynamic_array_t da, void *element)`:  
  _Finds the index of the first occurrence of an element._ _(Coming Soon) 🚀_  
- `da_last_index_of(dynamic_array_t da, void *element)`:  
  _Finds the index of the last occurrence._ _(Coming Soon) 🚀_
- `da_contains(dynamic_array_t da, void *element)`:  
  _Checks if the element exists in the array._ _(Coming Soon) 🚀_ 

---

## 5️⃣ Capacity and Size Management  

### 🔹 Size and Capacity Queries  
- `size_t da_size(dynamic_array_t da)`:  
  _Returns the number of elements currently stored._ 
- `da_capacity(dynamic_array_t da)`:  
  _Returns the current allocated capacity._ _(Coming Soon) 🚀_  
- `bool da_is_empty(dynamic_array_t da)`:  
  _Checks whether the array has any elements._  

### 🔹 Resizing and Memory Management  
- `da_reserve(dynamic_array_t da, size_t min_capacity)`:  
  _Ensures that the array has at least a certain capacity to minimize reallocations._ _(Coming Soon) 🚀_
- `da_shrink_to_fit(dynamic_array_t da)`:  
  _Reduces allocated capacity to match the current size._ _(Coming Soon) 🚀_

---

## 6️⃣ Utility Functions  

### 🔹 Iteration  
- `da_foreach(dynamic_array_t da, void (*function)(void*))`:  
  _Applies a given function to each element._ _(Coming Soon) 🚀_

### 🔹 Sorting and Reordering  
- `da_sort(dynamic_array_t da, int (*comparator)(const void*, const void*))`:  
  _Sorts the array using a comparator function._ _(Coming Soon) 🚀_
- `da_reverse(dynamic_array_t da)`:  
  _Reverses the order of the elements._ _(Coming Soon) 🚀_
- `da_shuffle(dynamic_array_t da)`:  
  _Randomly reorders the elements._ _(Coming Soon) 🚀_

### 🔹 Miscellaneous  
- `da_copy(dynamic_array_t *src)`:  
  _Creates a copy of the dynamic array._ _(Coming Soon) 🚀_
- `da_equals(dynamic_array_t da1, dynamic_array_t da2)`:  
  _Checks if two dynamic arrays are equivalent in content and order._ _(Coming Soon) 🚀_
- `da_swap(dynamic_array_t da, size_t index1, size_t index2)`:  
  _Swaps two elements at the specified indices._ _(Coming Soon) 🚀_

