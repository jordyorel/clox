
#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < len(chunk);) {
        offset = disassembleInstruction(chunk, offset);
    }
}

// Handles the disassembly of instructions that have a single operand (a
// constant). Parameters:
//   name - The name of the opcode to print (e.g., "OP_CONSTANT").
//   chunk - Pointer to the Chunk containing the bytecode instructions.
//   offset - The current index of the instruction.
// Returns:
//   The offset of the next instruction (current offset + 2).
static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = get_code(chunk, offset);
    printf("%-16s %4d '", name, constant);
    printValue(get_constant(chunk, offset));
    printf("'\n");
    return offset + 2;
}

// Disassembles a single instruction at a specific offset in the chunk.
// Parameters:
//   chunk - Pointer to the Chunk containing the bytecode instructions.
//   offset - The current index of the instruction to disassemble.
// Returns:
//   The offset of the next instruction after the one being disassembled.
int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    int current_line = get_line(chunk, offset);
    int previous_line = (offset > 0) ? get_line(chunk, offset - 1) : -1;
    if (offset > 0 && current_line == previous_line) {
        printf("    | ");
    } else {
        printf("%4d ", current_line);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT_LONG: {
            int constantIndex = (chunk->code[offset + 1] << 16) |
                                (chunk->code[offset + 2] << 8) |
                                chunk->code[offset + 3];
            printf("%-16s %4d '", "OP_CONSTANT_LONG", constantIndex);
            printValue(chunk->constants.values[constantIndex]);
            printf("'\n");
            return offset + 4;
        }
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

// Handles the disassembly of simple 1-byte instructions (no operands).
// Parameters:
//   name - The name of the opcode to print (e.g., "OP_ADD").
//   offset - The current index of the instruction.
// Returns:
//   The offset of the next instruction (current offset + 1).
int simpleInstruction(const char* name, int offset) {
    printf("%s \n", name);
    return offset + 1;
}
