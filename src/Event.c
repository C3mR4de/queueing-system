#include "Event.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Event* Event_Create(const EventType type, const TimeMoment time, const EventRelative relative)
{
    Event* const event = malloc(sizeof(Event));

    if (!event)
        return NULL;

    Event tmp = (Event)
    {
        .type     = type,
        .time     = time,
        .relative = relative
    };

    memcpy(event, &tmp, sizeof(Event));
    return event;
}

void Event_Destroy(Event* const event)
{
    free(event);
}
