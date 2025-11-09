#include "Vector.h"
#include <stdlib.h>
#include <assert.h>

struct Vector
{
    void** data;
    size_t size;
};

Vector* Vector_Create(const size_t size)
{
    Vector* const vector = malloc(sizeof(Vector));
    
    if (!vector)
        return NULL;

    *vector = (Vector)
    {
        .data     = malloc(size * sizeof(void*)),
        .size     = size
    };

    if (vector->data)
        return vector;

    free(vector);
    return NULL;
}

void Vector_Destroy(Vector* const vector)
{
    assert(vector);

    free(vector->data);
    free(vector);
}

void* Vector_Get(const Vector* const vector, const size_t index)
{
    assert(vector);
    assert(index < vector->size);

    return vector->data[index];
}

bool Vector_Set(Vector* const vector, const size_t index, void* const element)
{
    assert(vector);
    assert(index < vector->size);

    vector->data[index] = element;
    return true;
}

size_t Vector_Size(const Vector* const vector)
{
    assert(vector);
    return vector->size;
}
