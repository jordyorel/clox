#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum {
    OP_RETURN,
} opCode;


/* 
    Dynamic array of bytecode:
    capacity: Number of entries
    count: Number of used enties
    uint8_t: bytecode instruction
*/ 
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} Chunk;
 
void initChunk(Chunk* chunk);

#endif