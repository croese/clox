#include "lines.h"
#include "memory.h"
#include <stdlib.h>

void initLineGroupArray(LineGroupArray* array)
{
    array->count = 0;
    array->capacity = 0;
    array->groups = NULL;
}

void writeLineGroupArray(LineGroupArray* array, int index, int line)
{
    for (int i = 0; i < array->count; i++)
    {
        if (array->groups[i].line == line)
        {
            array->groups[i].lastIndex = index;
            return;
        }
    }

    // we didn't find an existing entry so add one, growing if needed
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->groups = GROW_ARRAY(LineGroup, array->groups, oldCapacity, array->capacity);
    }

    array->groups[array->count].lastIndex = index;
    array->groups[array->count].line = line;
    array->count++;
}

void freeLineGroupArray(LineGroupArray* array)
{
    FREE_ARRAY(LineGroup, array->groups, array->capacity);
    initLineGroupArray(array);
}
