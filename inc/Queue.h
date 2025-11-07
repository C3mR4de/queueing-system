#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Queue Queue;

Queue* Queue_Create(size_t capacity);
void   Queue_Destroy(Queue* queue);

bool   Queue_Enqueue(Queue* queue, void* element);
void*  Queue_Dequeue(Queue* queue);
bool   Queue_IsEmpty(const Queue* queue);
size_t Queue_Size(const Queue* queue);

#endif
