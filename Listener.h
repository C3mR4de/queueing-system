#ifndef LISTENER_H
#define LISTENER_H

#include "CommonTypedefs.h"
#include "Vector.h"
#include "Buffer.h"

typedef struct Listener Listener;

Listener* Listener_Create(void);
void      Listener_Destroy(Listener* listener);

void Listener_OnStep(Listener* listener, size_t step, TimeMoment time, const char* message, Vector* devices, Buffer buffer);
void Listener_OnFinish(Listener* Listener);

#endif
