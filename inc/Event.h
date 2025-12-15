#ifndef EVENT_H
#define EVENT_H

#include "Source.h"
#include "Device.h"

typedef enum { ARRIVAL, RELEASE } EventType;
typedef union
{
    Source* source;
    Device* device;
}
EventRelative;

typedef struct 
{
    EventType     const type;
    TimeMoment    const time;
    EventRelative const relative;
}
Event;

/// \brief Создаёт особое событие в динамической памяти.
///
/// \param[in] type     Тип особого события - поступление заявки (ARRIVAL) или освобождение прибора (RELEASE)
/// \param[in] time     Момент времени особого события
/// \param[in] relative Если type == ARRIVAL, источник заявки, если type == RELEASE, освобождаемый прибор
///
/// \return Дескриптор особого события
///
Event* Event_Create(EventType type, TimeMoment time, EventRelative relative);

/// \brief Удаляет особое событие из динамической памяти.
///
/// \param[in] event Дескриптор особого события
///
void Event_Destroy(Event* event);

#endif
