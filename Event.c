#include "Event.h"
#include <assert.h>

Event Event_CreateOnStack(Type type, TimeMoment time, Source* source, Device* device)
{
    return (Event)
    {
        .type   = type,
        .time   = time,
        .source = source,
        .device = device
    };
}

Event* Event_CreateOnHeap(const Type type, const TimeMoment time, Source* const source, Device* const device)
{
    Event* event = malloc(sizeof(Event));

    if (!event)
        return NULL;

    Event tmp = Event_CreateOnStack(type, time, source, device);
    memcpy(event, &tmp, sizeof(Event));
    return event;
}

void Event_Destroy(const Event* const event)
{
    free(event);
}
