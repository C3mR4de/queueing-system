#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct Queue Queue;

Queue* Queue_Create(size_t capacity);
bool   Queue_Enqueue(Queue* queue, void* element);
void*  Queue_Dequeue(Queue* queue);
bool   Queue_IsEmpty(const Queue* queue);
bool   Queue_Size(const Queue* queue);
void   Queue_Destroy(Queue* queue);

#endif
