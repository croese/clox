#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initLineGroupArray(&chunk->lines);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLineGroupArray(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    writeLineGroupArray(&chunk->lines, chunk->count, line);
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, Value value, int line)
{
    int constantIndex = addConstant(chunk, value);

    if (constantIndex < 256)
    {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, constantIndex, line);
    }
    else
    {
        writeChunk(chunk, OP_CONSTANT_LONG, line);

        uint8_t high = (constantIndex & 0xFF0000) >> 16;
        writeChunk(chunk, high, line);

        uint8_t mid = (constantIndex & 0xFF00) >> 8;
        writeChunk(chunk, mid, line);

        uint8_t low = constantIndex & 0xFF;
        writeChunk(chunk, low, line);
    }
}

int getLine(Chunk* chunk, int instructionIndex)
{
    LineGroupArray array = chunk->lines;
    for (int i = 0; i < array.count; i++)
    {
        LineGroup g = array.groups[i];
        if (instructionIndex <= g.lastIndex)
        {
            return g.line;
        }
    }

    return 0;
}
