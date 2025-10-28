#ifndef REQUEST_H
#define REQUEST_H

#include "CommonTypedefs.h"

typedef struct 
{
    ID         const source_id;
    TimeMoment const arrival_time;
    TimeMoment       service_start_time;
    TimeMoment       service_end_time;
}
Request;

Request    Request_Create(ID source_id, TimeMoment arrival_time);
TimeMoment Request_GetWaitTime(const Request* request);
TimeMoment Request_GetServiceTime(const Request* request);

#endif
