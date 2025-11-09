#include "Dispatcher.h"
#include <assert.h>

Device* Dispatcher_SelectDevice(Vector* devices)
{
    const size_t n = Vector_Size(devices);

    for (size_t i = 0; i < n; ++i)
    {
        Device* const device = Vector_Get(devices, i);

        if (!Device_IsBusy(device))
            return device;
    }

    return NULL;
}