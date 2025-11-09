#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Buffer Buffer;

Buffer* Buffer_Create(size_t capacity);
void    Buffer_Destroy(Buffer* buffer);

void* Buffer_Add(Buffer* buffer, void* element);
void* Buffer_Poll(Buffer* buffer);
bool  Buffer_IsEmpty(const Buffer* buffer);
bool  Buffer_Size(const Buffer* buffer);

#endif
