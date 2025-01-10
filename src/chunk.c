#include<stdlib.h>

#include "chunk.h"
#include "memory.h"

// Initializes a Chunk structure to its default state.
// Parameters:
//   chunk - Pointer to the Chunk to be initialized.
void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

// Frees the memory associated with a Chunk and resets it to its default state.
// Parameters:
//   chunk - Pointer to the Chunk to be freed.
void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

// Adds a byte (instruction) to the Chunk, growing its capacity if necessary.
// Parameters:
//   chunk - Pointer to the Chunk where the byte will be written.
//   byte - The byte (instruction) to add to the chunk.
void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        // chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->capacity = growCapacity(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, 
            oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, 
            oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

// Adds a constant value to the Chunk, returning the index where it was added.
// Parameters:
//   chunk - Pointer to the Chunk where the constant will be added.
//   value - The constant value to add to the chunk.
int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1; // Return the index of the constant -1 because the count is incremented before the value is added.
}
