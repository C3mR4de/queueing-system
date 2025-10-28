#include "Dispatcher.h"
#include <assert.h>

Dispatcher Dispatcher_Create(void)
{
    return (Dispatcher) { .last_used_device_index = -1 };
}

Device* Dispatcher_SelectDevice(Dispatcher* dispatcher, Vector* devices)
{
    assert(dispatcher != NULL);

    const size_t n = Vector_Size(devices);

    for (size_t i = 1; i <= n; ++i)
    {
        size_t index = (dispatcher->last_used_device_index + i) % n;

        if (!Device_IsBusy(Vector_Get(devices, index)))
        {
            dispatcher->last_used_device_index = index;
            return Vector_Get(devices, index);
        }

        return NULL;
    }
}