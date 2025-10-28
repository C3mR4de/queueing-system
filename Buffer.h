#ifndef BUFFER_H
#define BUFFER_H

#include "Queue.h"
#include "Request.h"

typedef struct
{
    size_t const capacity;
    Queue* const queue;
}
Buffer;

Buffer   Buffer_Create(size_t capacity);
bool     Buffer_Add(Buffer* buffer, Request* request);
Request* Buffer_Poll(Buffer* buffer);
bool     Buffer_IsEmpty(const Buffer* buffer);
size_t   Buffer_Size(const Buffer* buffer);

#endif
