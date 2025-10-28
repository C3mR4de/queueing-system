#include "Request.h"
#include <stddef.h>
#include <assert.h>

Request Request_Create(ID source_id, TimeMoment arrival_time)
{
    return (Request)
    {
        .source_id    = source_id,
        .arrival_time = arrival_time
    };
}

TimeMoment Request_GetWaitTime(const Request* const request)
{
    assert(request != NULL);
    return request->service_start_time - request->arrival_time;
}

TimeMoment Request_GetServiceTime(const Request* const request)
{
    assert(request != NULL);
    return request->service_end_time - request->service_start_time;
}
