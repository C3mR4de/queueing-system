#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "CommonTypedefs.h"
#include "Vector.h"
#include "Device.h"

/// \brief Выбирает первый свободный прибор (по приоритету номера).
///
/// \param[in] vector Массив приборов
///
/// \return Выбранный прибор (NULL, если все приборы заняты)
///
Device* Dispatcher_SelectDevice(Vector* devices);

#endif
