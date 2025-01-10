#include <stdio.h>

#include "debug.h"
#include "value.h"

// Disassembles all instructions in a given chunk and prints them in a
// human-readable format. Parameters:
//   chunk - Pointer to the Chunk containing the bytecode instructions.
//   name - A descriptive name for the chunk (useful for debugging).
void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for(int offset = 0; offset < chunk->count;) {
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
int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1]; // The operand is the next byte after the opcode.
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2; // The next instruction is 2 bytes away. Because the first byte is the opcode and the second byte is the operand.
}

// Disassembles a single instruction at a specific offset in the chunk.
// Parameters:
//   chunk - Pointer to the Chunk containing the bytecode instructions.
//   offset - The current index of the instruction to disassemble.
// Returns:
//   The offset of the next instruction after the one being disassembled.
int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset);
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