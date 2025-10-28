#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct Vector Vector;

Vector* Vector_Create(size_t capacity);
Vector* Vector_Get(Vector* vector, size_t index);
Vector* Vector_Size(Vector* vector);

#endif
