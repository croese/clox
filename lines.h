#ifndef CLOX_LINES_H
#define CLOX_LINES_H

typedef struct
{
    int line;
    int lastIndex;
} LineGroup;

typedef struct
{
    int count;
    int capacity;
    LineGroup* groups;
} LineGroupArray;

void initLineGroupArray(LineGroupArray* array);
void writeLineGroupArray(LineGroupArray* array, int index, int line);
void freeLineGroupArray(LineGroupArray* array);

#endif
