#include "Queue.h"

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

bool Queue_Enqueue(Queue* const queue, void* const element)
{
    if ((queue->tail + 1) % queue->capacity == queue->head)
        return false;
    
    queue->data[queue->tail] = element;
    queue->tail = (queue->tail + 1) % queue->capacity;
    ++queue->size;
}

void* Queue_Dequeue(Queue* const queue)
{
    if (Queue_IsEmpty(queue))
        return NULL;

    void* res = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    --queue->size;
    return res;
}

bool Queue_IsEmpty(const Queue* const queue)
{
    return queue->head == queue->tail;
}

bool Queue_Size(const Queue* const queue)
{
    return queue->size;
}

void Queue_Destroy(const Queue* const queue)
{
    free(queue->data);
    free(queue);
}
