
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
    // op constant
    OP_CONSTANT,
    OP_CONSTANT_LONG,

    // Binary op
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,

    // negate op
    OP_NEGATE,

    OP_RETURN,
    
} opCode;

typedef struct {
    int line;
    int run_length;
} LineInfo;

// Dynamic array of bytecode:
// count: Number of used entries
// capacity: Number of entries
// uint8_t: dynamic array of bytecode
// Lines: dynamic array of lines
// ValueArray: dynamic array of values
typedef struct {
    int count; // 4 bytes
    int capacity; // 4 bytes
    uint8_t* code; // 8 bytes : instrution
    LineInfo* line_info;
    int line_count; // 8 bytes
    int line_capcity;
    ValueArray constants; // 16 bytes
} Chunk; // 40 bytes 


void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* Chunk, Value value);
void writeConstant(Chunk* chunk, Value value, int line);
int len(Chunk* chunk);
int get_line(Chunk* chunk, int offset);
uint8_t get_code(Chunk* chunk, int offset);
Value get_constant(Chunk* chunk, int offset);


#endif
