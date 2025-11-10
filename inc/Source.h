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

/// \brief Генерирует заявку.
///
/// \param[in] source       Дескриптор источника
/// \param[in] current_time Момент генерации заявка
///
/// \return Дескриптор сгенерированной заявки
///
Request* Source_GenerateRequest(const Source* source, TimeMoment current_time);
double   Source_NextArrivalInterval(Source* source);

#endif
