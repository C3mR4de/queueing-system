#include "Source.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "Request.h"

struct Source
{
    ID      const id;
    MT19937       random;
    double  const min_interval;
    double  const max_interval;
};

Source* Source_Create(const ID id, const double min_interval, const double max_interval)
{
    assert(min_interval < max_interval);

    Source* const source = malloc(sizeof(Source));

    if (!source)
        return NULL;

    Source tmp = (Source)
    {
        .id           = id,
        .random       = MT19937_Create(time(NULL) / (id + 1)),
        .min_interval = min_interval,
        .max_interval = max_interval
    };

    memcpy(source, &tmp, sizeof(Source));
    return source;
}

void Source_Destroy(Source* const source)
{
    free(source);
}

Request* Source_GenerateRequest(const Source* const source, const TimeMoment current_time)
{
    assert(source);
    return Request_Create(source->id, current_time);
}

double Source_GenerateArrivalInterval(Source* const source)
{
    assert(source);
    return source->min_interval + (source->max_interval - source->min_interval) * MT19937_RandRange(&source->random, 0, 1);
}
