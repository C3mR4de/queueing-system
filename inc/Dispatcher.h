#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "CommonTypedefs.h"
#include "Vector.h"
#include "Device.h"

typedef struct
{
    size_t last_used_device_index;
}
Dispatcher;

Dispatcher Dispatcher_Create(void);
Device*    Dispatcher_SelectDevice(Dispatcher* dispatcher, Vector* devices);

#endif