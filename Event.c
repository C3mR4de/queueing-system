#include "Event.h"

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

void Event_Destroy(const Event* const event)
{
    free(event);
}
