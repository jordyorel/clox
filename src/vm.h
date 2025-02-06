
#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    //< testting
    uint8_t* code_end; // end of the code
    // testting >
    uint8_t* ip; // instruction pointer can also be called pc(program counter)
    Value* stack;
    Value* stackTop;
    int stackCapacity;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVm(VM* vm);
void freeVm(VM* vm);
InterpretResult interpret(const char* source);
void push(VM* vm, Value value);
Value pop(VM* vm);

#endif