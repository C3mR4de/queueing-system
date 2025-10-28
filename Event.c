#include "Event.h"
#include <assert.h>

struct Event
{
    Type       const type;
    TimeMoment const time;
    Source*    const source;
    Device*    const device;
};

Event* Event_Create(const Type type, const TimeMoment time, Source* const source, Device* const device)
{
    Event* event = malloc(sizeof(Event));

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

Type Event_GetType(const Event* const event)
{
    assert(event);
    return event->type;
}

Type Event_GetTime(const Event* const event)
{
    assert(event);
    return event->time;
}

Source* Event_GetSource(const Event* const event)
{
    assert(event);
    return event->source;
}

void Event_Destroy(const Event* const event)
{
    free(event);
}
