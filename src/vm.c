#include "vm.h"

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "debug.h"
#include "memory.h"

VM vm;

static void resetStack(VM* vm) {
    vm->stackTop = vm->stack;
}

void initVm(VM* vm) {
    vm->stackCapacity = STACK_MAX;  // Start with the initial capacity
    vm->stack = malloc(vm->stackCapacity * sizeof(Value));
    if (vm->stack == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the stack!\n");
        exit(1);
    }
    resetStack(vm);
    vm->stackTop = vm->stack;
    vm->chunk = NULL;
    vm->ip = NULL;
}

void freeVm(VM* vm) {
    free(vm->stack);
    vm->stack = NULL;
    vm->stackTop = NULL;
    vm->stackCapacity = 0;
}

void push(VM* vm, Value value) {
    GROW_STACK_IF_NEEDED(vm);
    *vm->stackTop = value;
    vm->stackTop++;
}

Value pop(VM* vm) {
    vm->stackTop--;
    return *vm->stackTop;
}

static InterpretResult run(VM* vm) {
    #define READ_BYTE() (*vm->ip++) // read the next byte and increment the instruction pointer
    #define READ_CONSTANT() (vm->chunk->constants.values[READ_BYTE()])
    #define READ_CONSTANT_LONG() \
        (vm->chunk->constants.values[ \
            (READ_BYTE() << 16 ) | \
            (READ_BYTE () << 8) | \
            (READ_BYTE()) \
        ])

    for(;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("Stack: [ ");
            for (Value* slot = vm->stack; slot < vm->stackTop; slot++) {
                printValue(*slot);
                if (slot < vm->stackTop - 1) {
                    printf(", ");
                }
            }
            printf(" ]");
            printf("\n");
            disassembleInstruction(vm->chunk, (int)(vm->ip - vm->chunk->code));
            printf("-----------------------------------------\n");
        #endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(vm, constant);
                break;
            }
            case OP_CONSTANT_LONG: {
                Value constant = READ_CONSTANT_LONG();
                push(vm, constant);
                break;
            }
            case OP_NEGATE:{
                Value top = pop(vm);
                push(vm, -top);
                break;
            }
            case OP_RETURN: {
                printf("last slot: ");
                printValue(pop(vm));
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef READ_CONSTANT_LONG
}

InterpretResult interpret(VM* vm, Chunk* chunk) {
    vm->chunk = chunk;
    vm->ip = vm->chunk->code;
    return run(vm);
}

