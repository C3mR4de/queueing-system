#ifndef REQUEST_H
#define REQUEST_H

#include "CommonTypedefs.h"

typedef struct 
{
    ID         const source_id;
    TimeMoment const arrival_time;
    TimeMoment       service_start_time;
    TimeMoment       service_end_time;
}
Request;

/// \brief Создаёт заявку.
///
/// \param[in] source_id    ID прибора, который будет обслуживать эту заявку
/// \param[in] arrival_time Время поступления заявки в систему
///
/// \return Дескриптор заявки (NULL в случае неудачи)
///
Request* Request_Create(ID source_id, TimeMoment arrival_time);

/// \brief Удаляет заявку.
///
/// \param[in] request Дескриптор заявки
///
void Request_Destroy(Request* request);

/// \brief Возвращает время ожидания заявки
///
/// \param[in] request Дескриптор заявки
///
/// \return Время ожидания заявки
///
TimeMoment Request_GetWaitTime(const Request* request);

/// \brief Возвращает время обслуживания заявки
///
/// \param[in] request Дескриптор заявки
///
/// \return Время обслуживания заявки
///
TimeMoment Request_GetServiceTime(const Request* request);

#endif
