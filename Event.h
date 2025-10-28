#ifndef EVENT_H
#define EVENT_H

#include "Source.h"
#include "Device.h"

typedef enum { ARRIVAL, RELEASE } Type;

typedef struct Event Event;

Event* Event_Create(Type type, TimeMoment time, Source* source, Device* device);
Type   Event_GetType(const Event* event);
Type   Event_GetTime(const Event* event);
Type   Event_GetSource(const Event* event);
void   Event_Destroy(const Event* event);

#endif
