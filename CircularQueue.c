#include "CircularQueue.h"
#include <stdlib.h>
#include <assert.h>

struct CircularQueue
{
    void** data;
    size_t size;
    size_t capacity;
    size_t enqueue_pos;
    size_t dequeue_pos;
};

CircularQueue* CircularQueue_Create(const size_t capacity)
{
    CircularQueue* const queue = malloc(sizeof(CircularQueue));

    if (!queue)
        return NULL;

    *queue = (CircularQueue)
    {
        .data        = calloc(1, capacity * sizeof(void*)),
        .size        = 0,
        .capacity    = capacity,
        .enqueue_pos = 0,
        .dequeue_pos = 0
    };

    if (queue->data)
        return queue;

    free(queue);
    return NULL;
}

void CircularQueue_Destroy(CircularQueue* const queue)
{
    assert(queue);

    free(queue->data);
    free(queue);
}

bool CircularQueue_Enqueue(CircularQueue* const queue, void* const element)
{
    assert(queue);
    assert(element);

    size_t counter = 0;

    while (counter < queue->capacity && queue->data[queue->enqueue_pos])
    {
        queue->enqueue_pos = (queue->enqueue_pos + 1) % queue->capacity;
        ++counter;
    }

    if (counter < queue->capacity)
    {
        queue->data[queue->enqueue_pos] = element;
        return true;
    }

    return false;
}

void* CircularQueue_Dequeue(CircularQueue* const queue)
{
    assert(queue);

    size_t counter = 0;

    while (counter < queue->capacity && !queue->data[queue->dequeue_pos])
    {
        queue->dequeue_pos = (queue->dequeue_pos + 1) % queue->capacity;
        ++counter;
    }

    if (counter < queue->capacity)
    {
        void* const element = queue->data[queue->dequeue_pos];
        queue->data[queue->dequeue_pos] = NULL;

        return element;
    }

    return NULL;
}

bool CircularQueue_IsEmpty(const CircularQueue* const queue)
{
    assert(queue);
    return !queue->size;
}

bool CircularQueue_Size(const CircularQueue* const queue)
{
    assert(queue);
    return queue->size;
}
