
#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* array) {
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

// Adds a value to the end of the array, growing the capacity if necessary.
// Parameters:
//   array - Pointer to the ValueArray where the value will be written.
//   value - The value to add to the array.
void writeValueArray(ValueArray* array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        // array->capacity = GROW_CAPACITY(oldCapacity);
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity); // Grow the array
    }

    array->values[array->count] = value;
    array->count++;
}

// Frees the memory associated with a ValueArray and resets it to its default state.
void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value) {
   printf("%g", value);
}
