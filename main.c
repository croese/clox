#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(int argc, char** argv)
{
    Chunk chunk;
    initChunk(&chunk);
    writeConstant(&chunk, 42, 10);
    writeConstant(&chunk, 1.2, 123);
    writeChunk(&chunk, OP_RETURN, 123);
    disassembleChunk(&chunk, "test chunk");
    // int line = getLine(&chunk, 2);
    // printf("line: %d\n", line);
    freeChunk(&chunk);
}
