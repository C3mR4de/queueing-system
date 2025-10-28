#include "Dispatcher.h"

Dispatcher Dispatcher_Create(void)
{
    return (Dispatcher) { .last_used_device_index = -1 };
}

Device* Dispatcher_SelectDevice(Dispatcher* dispatcher, Vector* devices)
{
    const size_t n = Vector_Size(devices);

    for (size_t i = 1; i <= n; ++i)
    {
        size_t index = (dispatcher->last_used_device_index + i) % n;

        if (!((Device*)Vector_Get(devices, index))->is_busy)
        {
            dispatcher->last_used_device_index = index;
            return Vector_Get(devices, index);
        }

        return NULL;
    }
}