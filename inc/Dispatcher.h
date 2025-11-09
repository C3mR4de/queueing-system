#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "CommonTypedefs.h"
#include "Vector.h"
#include "Device.h"

Device* Dispatcher_SelectDevice(Vector* devices);

#endif
