#ifndef DEVICE_H
#define DEVICE_H

#include <stdbool.h>
#include "Request.h"

typedef struct Device Device;

/// \brief Создаёт прибор в динамической памяти.
///
/// \param[in] ID Идентификатор прибора
///
/// \return Дескриптор прибора (NULL в случае неудачи)
///
Device* Device_Create(ID id);

/// \brief Удаляет прибор из динамической памяти.
///
/// \param[in] device Дескриптор прибора
///
void Device_Destroy(Device* device);

/// \brief Начинает обслуживание заявки на приборе.
///
/// \param[in] device       Дескриптор прибора
/// \param[in] request      Дескриптор заявки
/// \param[in] current_time Начало обслуживания заявки
/// \param[in] service_time Длительность обслуживания заявки
///
void Device_StartService(Device* device, Request* request, TimeMoment current_time, double service_time);

/// \brief Завершает обслуживание заявки на приборе.
///
/// \param[in] device Дескриптор прибора
///
Request* Device_FinishService(Device* device);

/// \brief Проверяет, не является ли прибор занятым.
///
/// \param[in] device Дескриптор прибора
///
bool Device_IsBusy(const Device* device);

/// \brief Возвращает момент, в который прибор должен быть освобождён.
///
/// \param[in] device Дескриптор прибора
///
/// \return Момент времени, когда прибор будет освобождён (-1, если прибор свободен)
///
TimeMoment Device_GetPlannedReleaseTime(const Device* device);

#endif
