
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"



static void repl() {
    // VM vm;
    // initVm(&vm);
    char line[1024];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        interpret( line);
    }
    // freeVm(&vm);
}

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Couldn't opn=en the file \"%s\". \n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(sizeof(fileSize + 1));
    size_t byteRead = fread(buffer, sizeof(char), fileSize, file);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\". \n", path);
    }
    
    buffer[byteRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(const char* path) {
    // VM vm;
    // initVm(&vm);
    char* source = readFile(path);
    InterpretResult result = interpret(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);

    // freeVm(&vm);
}

int main(int argc, const char* argv[]) {
    VM vm;
    initVm(&vm);

    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: clox: [Path]\n");
    }


    
    Chunk chunk;
    initChunk(&chunk);

    writeConstant(&chunk, 1.2, 123);
    writeConstant(&chunk, 3.14, 123);
    // writeChunk(&chunk, OP_ADD, 123);

    // writeConstant(&chunk, 0.0, 123);
    // writeConstant(&chunk, 1.0, 123);
    // writeChunk(&chunk, OP_ADD, 123);  // Adds 0 + 1

    // writeConstant(&chunk, 2.0, 123);
    writeChunk(&chunk, OP_MULTIPLY, 123);

    // Add enough constants to exceed 255
    // for (int i = 0; i < 300; i++) {
    //     writeConstant(&chunk, (double)i, 123);
    // }


    // writeChunk(&chunk, OP_NEGATE, 123);
    writeChunk(&chunk, OP_RETURN, 125);

    // disassembleChunk(&chunk, "Test Chunk");
    // interpret(&vm, &chunk);
    freeVm(&vm);

    freeChunk(&chunk);
    return 0;
}
