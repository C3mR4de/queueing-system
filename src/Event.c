#include "Event.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Event* Event_Create(const Type type, const TimeMoment time, Source* const source, Device* const device)
{
    Event* const event = malloc(sizeof(Event));

    if (!event)
        return NULL;

    Event tmp = (Event)
    {
        .type   = type,
        .time   = time,
        .source = source,
        .device = device
    };

    memcpy(event, &tmp, sizeof(Event));
    return event;
}

void Event_Destroy(Event* const event)
{
    free(event);
}
