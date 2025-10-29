#ifndef DEVICE_H
#define DEVICE_H

#include <stdbool.h>
#include "Request.h"

typedef struct Device Device;

Device* Device_Create(ID id);
void    Device_Destroy(Device* device);

void       Device_StartService(Device* device, Request* request, TimeMoment current_time, double service_time);
Request*   Device_FinishService(Device* device);
bool       Device_IsBusy(const Device* device);
TimeMoment Device_GetPlannedReleaseTime(const Device* device);

#endif
