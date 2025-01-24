
#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"



int main(int argc, const char* argv[]) {
    VM vm;
    initVm(&vm);
    
    Chunk chunk;
    initChunk(&chunk);

    // writeConstant(&chunk, 1.2, 123);
    // writeConstant(&chunk, 3.14, 123);
    // writeConstant(&chunk, 999.9, 123);

    // Add enough constants to exceed 255
    for (int i = 0; i < 5; i++) {
        writeConstant(&chunk, (double)i, 123);
    }
    writeChunk(&chunk, OP_NEGATE, 123);

    writeChunk(&chunk, OP_RETURN, 125);


    // disassembleChunk(&chunk, "Test Chunk");
    interpret(&vm, &chunk);
    freeVm(&vm);

    freeChunk(&chunk);
    return 0;
}
