#ifndef EVENT_H
#define EVENT_H

#include "Source.h"
#include "Device.h"

typedef enum { ARRIVAL, RELEASE } Type;

typedef struct 
{
    Type       const type;
    TimeMoment const time;
    Source*    const source;
    Device*    const device;
}
Event;

/// \brief Создаёт особое событие в динамической памяти.
///
/// \param[in] type   Тип особого события - поступление заявки (ARRIVAL) или освобождение прибора (RELEASE)
/// \param[in] time   Момент времени особого события
/// \param[in] source Источник заявки (если type == ARRIVAL, иначе NULL)
/// \param[in] device Освобождаемый прибор (если type == RELEASE, иначе NULL)
///
/// \return Дескриптор особого события
///
Event* Event_Create(Type type, TimeMoment time, Source* source, Device* device);

/// \brief Удаляет особое событие из динамической памяти.
///
/// \param[in] event Дескриптор особого события
///
void Event_Destroy(Event* event);

#endif
