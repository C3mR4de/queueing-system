#include "Source.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Request.h"

Source Source_Create(const ID id, const double min_interval, const double max_interval)
{
    return (Source)
    {
        .id           = id,
        .random       = MT19937_Create(time(NULL)),
        .min_interval = min_interval,
        .max_interval = max_interval
    };
}

Request* Source_GenerateRequest(Source* const source, const TimeMoment current_time)
{
    Request* const new_request = malloc(sizeof(Request));
    Request  const tmp         = Request_Create(source->id, current_time);
    memcpy(new_request, &tmp, sizeof(Request));
    return new_request;
}

double Source_NextArrivalInterval(Source* const source)
{
    return source->min_interval + (source->max_interval - source->min_interval) * MT19937_RandRange(&source->random, 0, 1);
}
