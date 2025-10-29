#ifndef SOURCE_H
#define SOURCE_H

#include "CommonTypedefs.h"
#include "MT19937.h"
#include "Request.h"

typedef struct Source Source;

Source*  Source_Create(ID id, double min_interval, double max_interval);
Request* Source_GenerateRequest(const Source* source, TimeMoment current_time);
double   Source_NextArrivalInterval(Source* source);
void     Source_Destroy(Source* source);

#endif
