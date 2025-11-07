#include "Queue.h"
#include <stdlib.h>
#include <assert.h>

struct Queue
{
    void** data;
    size_t size;
    size_t capacity;
    size_t head;
    size_t tail;
};

Queue* Queue_Create(const size_t capacity)
{
    Queue* const queue = malloc(sizeof(Queue));

    if (!queue)
        return NULL;

    const size_t real_capacity = capacity + 1;

    *queue = (Queue)
    {
        .data     = malloc(real_capacity * sizeof(void*)),
        .size     = 0,
        .capacity = real_capacity,
        .head     = 0,
        .tail     = 0
    };

    if (queue->data)
        return queue;

    free(queue);
    return NULL;
}

void Queue_Destroy(Queue* const queue)
{
    assert(queue);

    free(queue->data);
    free(queue);
}

bool Queue_Enqueue(Queue* const queue, void* const element)
{
    assert(queue);

    if ((queue->tail + 1) % queue->capacity == queue->head)
        return false;
    
    queue->data[queue->tail] = element;
    queue->tail = (queue->tail + 1) % queue->capacity;
    ++queue->size;

    return true;
}

void* Queue_Dequeue(Queue* const queue)
{
    assert(queue);

    if (Queue_IsEmpty(queue))
        return NULL;

    void* const res = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    --queue->size;

    return res;
}

bool Queue_IsEmpty(const Queue* const queue)
{
    assert(queue);
    return queue->head == queue->tail;
}

size_t Queue_Size(const Queue* const queue)
{
    assert(queue);
    return queue->size;
}
