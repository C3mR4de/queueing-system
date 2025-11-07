#include "Buffer.h"
#include <assert.h>

Buffer Buffer_Create(size_t capacity)
{
    return (Buffer)
    {
        .capacity = capacity,
        .queue    = CircularQueue_Create(capacity)
    };
}

void Buffer_Destroy(Buffer* const buffer)
{
    assert(buffer);
    CircularQueue_Destroy(buffer->queue);
}

bool Buffer_Add(Buffer* const buffer, Request* const request)
{
    assert(buffer);
    return CircularQueue_Enqueue(buffer->queue, request);
}

Request* Buffer_Poll(Buffer* const buffer)
{
    assert(buffer);
    return CircularQueue_Dequeue(buffer->queue);
}

bool Buffer_IsEmpty(const Buffer* const buffer)
{
    assert(buffer);
    return CircularQueue_IsEmpty(buffer->queue);
}

size_t Buffer_Size(const Buffer* const buffer)
{
    assert(buffer);
    return CircularQueue_Size(buffer->queue);
}
