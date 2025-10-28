#include "Device.h"
#include <stddef.h>

Device Device_Create(const ID id)
{
    return (Device){ .id = id };
}

void Device_StartService(Device* const device, Request* request, const TimeMoment current_time, const double service_time)
{
    device->is_busy = true;
    device->current_request = request;

    request->service_start_time = current_time;
    request->service_end_time = current_time + (TimeMoment)service_time;
}

void Device_FinishService(Device* const device)
{
    device->is_busy = false;
    Request* finished = device->current_request;
    device->current_request = NULL;
    return finished;
}

TimeMoment Device_GetPlannedReleaseTime(Device* const device)
{
    const Request* const cur = device->current_request;
    return cur ? cur->service_end_time : -1;
}
