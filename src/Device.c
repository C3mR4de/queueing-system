#include "Device.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

struct Device
{
    ID       const id;
    bool           is_busy;
    Request*       current_request;
};

Device* Device_Create(const ID id)
{
    Device* const device = malloc(sizeof(Device));

    if (!device)
        return NULL;
    
    Device tmp = (Device) { .id = id };
    memcpy(device, &tmp, sizeof(Device));
    return device;
}

void Device_Destroy(Device* const device)
{
    free(device);
}

void Device_StartService(Device* const device, Request* const request, const TimeMoment current_time, const double service_time)
{
    assert(device);

    device->is_busy         = true;
    device->current_request = request;

    request->service_start_time = current_time;
    request->service_end_time   = current_time + (TimeMoment)service_time;
}

Request* Device_FinishService(Device* const device)
{
    assert(device);

    device->is_busy = false;
    Request* const finished = device->current_request;
    device->current_request = NULL;

    return finished;
}

bool Device_IsBusy(const Device* const device)
{
    assert(device);
    return device->is_busy;
}

TimeMoment Device_GetPlannedReleaseTime(const Device* const device)
{
    assert(device);
    const Request* const cur = device->current_request;
    return cur ? cur->service_end_time : -1;
}
