#ifndef clox_value_h

#define clox_value_h

#include "common.h"

typedef double Value;


// A dynamic array of Value elements.
// Parameters:
//   capacity - The number of elements that the array can hold before it needs to grow.
//   count - The number of elements currently in the array.
//   values - A pointer to the first element in the array.
typedef struct {
    int capacity; // 4 bytes
    int count; // 4 bytes
    Value* values; // 8 bytes
} ValueArray; // 16 bytes

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);


#endif