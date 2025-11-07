#ifndef EVENT_H
#define EVENT_H

#include "Source.h"
#include "Device.h"

typedef enum { ARRIVAL, RELEASE } Type;

typedef struct 
{
    Type       const type;
    TimeMoment const time;
    Source*    const source;
    Device*    const device;
}
Event;

Event* Event_Create(Type type, TimeMoment time, Source* source, Device* device);
void   Event_Destroy(Event* event);

#endif
