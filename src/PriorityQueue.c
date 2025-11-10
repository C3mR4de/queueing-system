#include "PriorityQueue.h"
#include <stdlib.h>
#include <assert.h>

struct PriorityQueue
{
    void**     data;
    Comparator comparator;
    size_t     size;
    size_t     capacity;
    size_t     head;
    size_t     tail;
};

PriorityQueue* PriorityQueue_Create(const size_t capacity, const Comparator comparator)
{
    PriorityQueue* const queue = malloc(sizeof(PriorityQueue));

    if (!queue)
        return NULL;

    const size_t real_capacity = capacity + 1;

    *queue = (PriorityQueue)
    {
        .data       = malloc(real_capacity * sizeof(void*)),
        .comparator = comparator, 
        .size       = 0,
        .capacity   = real_capacity,
        .head       = 0,
        .tail       = 0
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

bool PriorityQueue_Enqueue(PriorityQueue* const queue, void* const element)
{
    assert(queue);
    assert(element);

    if ((queue->tail + 1) % queue->capacity == queue->head)
        return false;
    
    queue->data[queue->tail] = element;
    queue->tail = (queue->tail + 1) % queue->capacity;
    ++queue->size;

    return true;
}

void* PriorityQueue_Dequeue(PriorityQueue* const queue)
{
    assert(queue);

    if (PriorityQueue_IsEmpty(queue))
        return NULL;

    void* const res = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    --queue->size;

    return res;
}

bool PriorityQueue_IsEmpty(const PriorityQueue* const queue)
{
    assert(queue);
    return queue->head == queue->tail;
}

size_t PriorityQueue_Size(const PriorityQueue* const queue)
{
    assert(queue);
    return queue->size;
}
