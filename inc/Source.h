#ifndef SOURCE_H
#define SOURCE_H

#include "CommonTypedefs.h"
#include "MT19937.h"
#include "Request.h"

typedef struct Source Source;

/// \brief Создаёт источник в динамической памяти.
///
/// \param[in] source_id    ID источника
/// \param[in] min_interval Минимальное время обработки заявки
/// \param[in] min_interval Максимальное время обработки заявки
///
/// \return Дескриптор источника (NULL в случае неудачи)
///
Source* Source_Create(ID id, double min_interval, double max_interval);

/// \brief Удаляет источник из динамической памяти.
///
/// \param[in] source Дескриптор источника
///
void Source_Destroy(Source* source);

/// \brief Возвращает ID источника.
///
/// \param[in] device Дескриптор источника
///
/// \return ID источника
///
ID Source_GetID(const Source* device);

/// \brief Генерирует заявку.
///
/// \param[in] source       Дескриптор источника
/// \param[in] current_time Момент генерации заявки
///
/// \return Дескриптор сгенерированной заявки
///
Request* Source_GenerateRequest(const Source* source, TimeMoment current_time);

/// \brief Генерирует интервал прибытия заявки.
///
/// \param[in] source Дескриптор источника
///
/// \return Интервал прибытия заявки
///
double Source_GenerateArrivalInterval(Source* source);

/// \brief Добавляет обработанную заявку.
///
/// \param[in] source Дескриптор источника
///
void Source_ArriveRequest(Source* source);

/// \brief Возвращает массив времён прибытия заявок.
///
/// \param[in] source Дескриптор источника
///
/// \return Массив времён прибытия заявок
///
TimeMoment* Source_GetRequestsArrival(Source* source);

/// \brief Возвращает время прибытия следующей заявки.
///
/// \param[in] source Дескриптор источника
///
/// \return Время прибытия следующей заявки
///
TimeMoment Source_GetNextRequestArrivalTime(const Source* source);

#endif
