#include "Vector.h"
#include <stdlib.h>
#include <assert.h>

struct Vector
{
    void** data;
    size_t size;
    size_t capacity;
};

Vector* Vector_Create(const size_t capacity)
{
    Vector* vector = malloc(sizeof(Vector));
    
    if (!vector)
        return NULL;

    *vector = (Vector)
    {
        .data     = malloc(capacity * sizeof(void*)),
        .size     = 0,
        .capacity = capacity,
    };

    if (vector->data)
        return vector;

    free(vector);
    return NULL;
}

void* Vector_Get(const Vector* const vector, const size_t index)
{
    assert(vector);

    if (index >= vector->size)
        return NULL;

    return vector->data[index];
}

bool Vector_Set(Vector* const vector, const size_t index, void* const element)
{
    assert(vector);

    if (index >= vector->size)
        return false;

    vector->data[index] = element;
    return true;
}

size_t Vector_Size(const Vector* const vector)
{
    assert(vector);
    return vector->size;
}

void Vector_Destroy(Vector* const vector)
{
    assert(vector);

    free(vector->data);
    free(vector);
}
