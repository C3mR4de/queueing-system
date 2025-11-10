#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vector.h"
#include "Source.h"
#include "Device.h"
#include "Buffer.h"
#include "Dispatcher.h"
#include "Listener.h"
#include "MT19937.h"

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
void Simulation_Destroy(Simulation* Simulation);

/// \brief Делает шаг в симуляции от текущего особого события к следующему.
///
/// \return false, если симуляция окончена, true в противном случае
///
bool Simulation_Step(Simulation* simulation);

#endif
