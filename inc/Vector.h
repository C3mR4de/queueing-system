#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Vector Vector;

Vector* Vector_Create(size_t size);
void    Vector_Destroy(Vector* const vector);

void*  Vector_Get(const Vector* vector, size_t index);
bool   Vector_Set(Vector* vector, size_t index, void* element);
size_t Vector_Size(const Vector* vector);

#endif
