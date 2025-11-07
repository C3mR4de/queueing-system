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

Simulation* Simulation_Create(size_t num_sources,
                              size_t num_devices,
                              size_t buffer_size,
                              double min_interval,
                              double max_interval,
                              double service_rate,
                              TimeMoment max_time);
void Simulation_Destroy(Simulation* Simulation);

bool Simulation_Step(Simulation* simulation);

#endif
