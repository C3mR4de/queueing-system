#ifndef SOURCE_H
#define SOURCE_H

#include "CommonTypedefs.h"
#include "MT19937.h"

typedef struct
{
    ID      const id;
    MT19937 const random;
    double  const min_interval;
    double  const max_interval;
}
Source;

Source   Source_Create(ID id, double min_interval, double max_interval);
Request* Source_GenerateRequest(Source* source, TimeMoment current_time);
double   Source_NextArrivalInterval(Source* source);

#endif
