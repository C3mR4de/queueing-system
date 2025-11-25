#include "PriorityQueue.h"
#include <stdlib.h>
#include <assert.h>

struct PriorityQueue
{
    void**     data;
    Comparator comparator;
    size_t     size;
    size_t     capacity;
};

PriorityQueue* PriorityQueue_Create(const size_t capacity, const Comparator comparator)
{
    assert(comparator);

    PriorityQueue* const queue = malloc(sizeof(PriorityQueue));

    if (!queue)
        return NULL;

    *queue = (PriorityQueue)
    {
        .data       = calloc(1, capacity * sizeof(void*)),
        .comparator = comparator, 
        .size       = 0,
        .capacity   = capacity,
    };

    if (queue->data)
        return queue;

    free(queue);
    return NULL;
}

void PriorityQueue_Destroy(PriorityQueue* const queue)
{
    assert(queue);

    free(queue->data);
    free(queue);
}

bool PriorityQueue_Enqueue(PriorityQueue* const restrict queue, void* const restrict element)
{
    assert(queue);
    assert(element);

    for (size_t i = 0; i < queue->capacity; ++i)
    {
        if (!queue->data[i])
        {
            queue->data[i] = element;
            ++queue->size;
            return true;
        }
    }

    return false;
}

void* PriorityQueue_Dequeue(PriorityQueue* const queue)
{
    assert(queue);

    void*  res   = NULL;
    size_t index = 0;

    for (size_t i = 0; i < queue->capacity; ++i)
    {
        if (queue->comparator(queue->data[i], res))
        {
            res   = queue->data[i];
            index = i;
        }
    }

    if (res)
    {
        queue->data[index] = NULL;
        --queue->size;
    }

    return res;
}

const void* PriorityQueue_Peek(const PriorityQueue* const queue)
{
    assert(queue);
    const void* res = NULL;

    for (size_t i = 0; i < queue->capacity; ++i)
    {
        if (queue->comparator(queue->data[i], res))
            res = queue->data[i];
    }

    return res;
}

bool PriorityQueue_IsEmpty(const PriorityQueue* const queue)
{
    assert(queue);
    return queue->size == 0;
}

size_t PriorityQueue_Size(const PriorityQueue* const queue)
{
    assert(queue);
    return queue->size;
}
