#ifndef DEVICE_H
#define DEVICE_H

#include <stdbool.h>
#include "Request.h"

typedef struct
{
    ID       const id;
    bool           is_busy;
    Request*       current_request;
}
Device;

Device     Device_Create(ID id);
void       Device_StartService(Device* device, Request* request, TimeMoment current_time, double service_time);
Request*   Device_FinishService(Device* device);
TimeMoment Device_GetPlannedReleaseTime(Device* device);

#endif
