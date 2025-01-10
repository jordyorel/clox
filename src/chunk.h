#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/// Enum representing the possible bytecode operations.
///
/// This enum defines the operations supported in the bytecode,
/// each corresponding to a unique byte value. The values represent
/// the different operations that can be performed in the virtual machine.
typedef enum {
    OP_RETURN,
    OP_CONSTANT,
} opCode;

// Dynamic array of bytecode:
// count: Number of used entries
// capacity: Number of entries
// uint8_t: dynamic array of bytecode
// ValueArray: dynamic array of values
typedef struct {
    int count; // 4 bytes
    int capacity; // 4 bytes
    uint8_t* code; // 8 bytes
    int* lines; // 8 bytes
    ValueArray constants; // 16 bytes
} Chunk; // 40 bytes
 
void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* Chunk, Value value);

#endif
