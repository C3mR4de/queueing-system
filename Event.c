#include "Event.h"

Event Event_Create(const Type type, const TimeMoment time, Source* const source, Device* const device)
{
    return (Event)
    {
        .type   = type,
        .time   = time,
        .source = source,
        .device = device
    };
}
