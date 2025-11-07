#include "Buffer.h"
#include <stdlib.h>
#include <assert.h>

struct Buffer
{
    void** data;
    size_t size;
    size_t capacity;
    size_t add_pos;
    size_t poll_pos;
};

Buffer* Buffer_Create(const size_t capacity)
{
    Buffer* const buffer = malloc(sizeof(Buffer));

    if (!buffer)
        return NULL;

    *buffer = (Buffer)
    {
        .data     = calloc(1, capacity * sizeof(void*)),
        .size     = 0,
        .capacity = capacity,
        .add_pos  = 0,
        .poll_pos = 0
    };

    if (buffer->data)
        return buffer;

    free(buffer);
    return NULL;
}

void Buffer_Destroy(Buffer* const buffer)
{
    assert(buffer);

    free(buffer->data);
    free(buffer);
}

bool Buffer_Add(Buffer* const buffer, void* const element)
{
    assert(buffer);
    assert(element);

    size_t counter = 0;

    while (counter < buffer->capacity && buffer->data[buffer->add_pos])
    {
        buffer->add_pos = (buffer->add_pos + 1) % buffer->capacity;
        ++counter;
    }

    if (counter < buffer->capacity)
    {
        buffer->data[buffer->add_pos] = element;
        return true;
    }

    return false;
}

void* Buffer_Poll(Buffer* const buffer)
{
    assert(buffer);

    size_t counter = 0;

    while (counter < buffer->capacity && !buffer->data[buffer->poll_pos])
    {
        buffer->poll_pos = (buffer->poll_pos + 1) % buffer->capacity;
        ++counter;
    }

    if (counter < buffer->capacity)
    {
        void* const element = buffer->data[buffer->poll_pos];
        buffer->data[buffer->poll_pos] = NULL;

        return element;
    }

    return NULL;
}

bool Buffer_IsEmpty(const Buffer* const buffer)
{
    assert(buffer);
    return !buffer->size;
}

bool Buffer_Size(const Buffer* const buffer)
{
    assert(buffer);
    return buffer->size;
}
