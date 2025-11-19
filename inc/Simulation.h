#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vector.h"
#include "Source.h"
#include "Device.h"
#include "Buffer.h"
#include "Dispatcher.h"
#include "MT19937.h"
#include "PriorityQueue.h"

typedef struct Simulation Simulation;

/// \brief Создаёт симуляцию в динамической памяти.
///
/// \param[in] num_sources  Количество источников
/// \param[in] num_devices  Количество приборов
/// \param[in] buffer_size  Размер буфера заявок
/// \param[in] min_interval Минимальный интервал между заявками, поступающими с одного прибора
/// \param[in] max_interval Максимальный интервал между заявками, поступающими с одного прибора
/// \param[in] service_rate Сервис-рейт
/// \param[in] max_time     Максимальная длительность симуляции
///
/// \return Дескриптор симуляции (NULL в случае неудачи)
///
Simulation* Simulation_Create(size_t num_sources,
                              size_t num_devices,
                              size_t buffer_size,
                              double min_interval,
                              double max_interval,
                              double service_rate,
                              TimeMoment max_time);

/// \brief Удаляет симуляцию в динамической памяти.
///
/// \param[in] simulation Дескриптор симуляции
///
void Simulation_Destroy(Simulation* Simulation);

/// \brief Делает шаг в симуляции от текущего особого события к следующему.
///
/// \return false, если симуляция окончена, true в противном случае
///
bool Simulation_Step(Simulation* simulation);

/// \brief Возвращает вектор приборов.
///
/// \return Вектор приборов
///
const Vector* Simulation_GetDevices(const Simulation* simulation);

/// \brief Возвращает буфер заявок.
///
/// \return Буфер заявок
///
const Buffer* Simulation_GetBuffer(const Simulation* simulation);

/// \brief Возвращает очередь событий.
///
/// \return Очередь событий
///
const PriorityQueue* Simulation_GetEventQueue(const Simulation* simulation);

#endif
