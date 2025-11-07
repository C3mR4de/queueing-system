#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct CircularQueue CircularQueue;

CircularQueue* CircularQueue_Create(size_t capacity);
void           CircularQueue_Destroy(CircularQueue* queue);

bool  CircularQueue_Enqueue(CircularQueue* queue, void* element);
void* CircularQueue_Dequeue(CircularQueue* queue);
bool  CircularQueue_IsEmpty(const CircularQueue* queue);
bool  CircularQueue_Size(const CircularQueue* queue);

#endif
