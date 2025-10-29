#include "Request.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Request* Request_Create(ID source_id, TimeMoment arrival_time)
{
    Request* request = malloc(sizeof(Request));

    if (!request)
        return NULL;

    Request tmp = (Request)
    {
        .source_id    = source_id,
        .arrival_time = arrival_time
    };

    memcpy(request, &tmp, sizeof(Request));
    return request;
}

TimeMoment Request_GetWaitTime(const Request* const request)
{
    assert(request);
    return request->service_start_time - request->arrival_time;
}

TimeMoment Request_GetServiceTime(const Request* const request)
{
    assert(request);
    return request->service_end_time - request->service_start_time;
}
