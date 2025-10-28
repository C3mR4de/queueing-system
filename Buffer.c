#include "Buffer.h"
#include <assert.h>

Buffer Buffer_Create(size_t capacity)
{
    return (Buffer)
    {
        .capacity = capacity,
        .queue    = Queue_Create(capacity)
    };
}

bool Buffer_Add(Buffer* const buffer, Request* const request)
{
    assert(buffer != NULL);
    return Queue_Enqueue(buffer->queue, request);
}

Request* Buffer_Poll(Buffer* const buffer)
{
    assert(buffer != NULL);
    return Queue_Dequeue(buffer->queue);
}

bool Buffer_IsEmpty(const Buffer* const buffer)
{
    assert(buffer != NULL);
    return Queue_IsEmpty(buffer->queue);
}

size_t Buffer_Size(const Buffer* const buffer)
{
    assert(buffer != NULL);
    return Queue_Size(buffer->queue);
}
