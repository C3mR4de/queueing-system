#include "Simulation.h"
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Listener.h"
#include "Event.h"
#include "Queue.h"

struct Simulation
{
    Vector*    sources;
    Vector*    devices;
    Buffer*    buffer;
    Queue*     event_queue;
    MT19937    random;
    Listener*  listener;

    size_t     step_counter;
    TimeMoment current_time;
    TimeMoment max_time;
    double     service_rate;
};

Simulation* Simulation_Create(const size_t num_sources,
                              const size_t num_devices,
                              const size_t buffer_size,
                              const double min_interval,
                              const double max_interval,
                              const double service_rate,
                              const TimeMoment max_time)
{
    Simulation* const simulation = malloc(sizeof(Simulation));

    if (!simulation)
        return NULL;

    Simulation tmp = (Simulation)
    {
        .sources      = Vector_Create(num_sources),
        .devices      = Vector_Create(num_devices),
        .buffer       = Buffer_Create(buffer_size),
        .event_queue  = Queue_Create(num_sources),
        .random       = MT19937_Create(time(NULL)),
        .listener     = Listener_Create(),
        .step_counter = 0,
        .current_time = 0,
        .max_time     = max_time,
        .service_rate = service_rate,
    };

    if (!(tmp.sources && tmp.devices && tmp.buffer && tmp.event_queue && tmp.listener))
        goto cleanup;

    for (size_t i = 0; i < num_sources; ++i)
    {
        Source* const add_source = Source_Create(i, min_interval, max_interval);

        if (!add_source)
            goto cleanup;

        Vector_Set(tmp.sources, i, add_source);
    }

    for (size_t i = 0; i < num_devices; ++i)
    {
        Device* const add_device = Device_Create(i);

        if (!add_device)
            goto cleanup;

        Vector_Set(tmp.devices, i, add_device);
    }

    for (size_t i = 0; i < num_sources; ++i)
    {
        Source*    const s = Vector_Get(tmp.sources, i);
        TimeMoment const t = (TimeMoment)Source_NextArrivalInterval(s);
        Queue_Enqueue(tmp.event_queue, Event_Create(ARRIVAL, t, s, NULL));
    }

    memcpy(simulation, &tmp, sizeof(Simulation));
    return simulation;

cleanup:

    Simulation_Destroy(&tmp);
    return NULL;
}

void Simulation_Destroy(Simulation* const simulation)
{
    assert(simulation);

    free(simulation->listener);

    while (!Queue_IsEmpty(simulation->event_queue))
        Event_Destroy(Queue_Dequeue(simulation->event_queue));

    Queue_Destroy(simulation->event_queue);

    while (!Buffer_IsEmpty(simulation->buffer))
        Request_Destroy(Buffer_Poll(simulation->buffer));

    Buffer_Destroy(simulation->buffer);

    if (simulation->devices)
    {
        for (size_t i = 0; i < Vector_Size(simulation->devices); ++i)
            Device_Destroy(Vector_Get(simulation->devices, i));

        Vector_Destroy(simulation->devices);
    }

    if (simulation->sources)
    {
        for (size_t i = 0; i < Vector_Size(simulation->sources); ++i)
            Source_Destroy(Vector_Get(simulation->sources, i));

        Vector_Destroy(simulation->sources);
    }

    free(simulation);
}

bool Simulation_Step(Simulation* const simulation)
{
    assert(simulation);

    if (simulation->current_time > simulation->max_time)
        return false;

    Event* const e = Queue_Dequeue(simulation->event_queue);

    if (!e)
        return false;

    simulation->current_time = e->time;
    ++simulation->step_counter;

    switch (e->type)
    {
        case ARRIVAL:

            Request* const request = Source_GenerateRequest(e->source, simulation->current_time);
            Device*  const device  = Dispatcher_SelectDevice(simulation->devices);

            if (device)
            {
                const double service_time = -log(1 - MT19937_RandRange(&simulation->random, 0, 1) / simulation->service_rate);
                Device_StartService(device, request, simulation->current_time, service_time);
                Queue_Enqueue(simulation->event_queue, Event_Create(RELEASE, simulation->current_time + (TimeMoment)service_time, NULL, device));
            }
            else
                Request_Destroy(Buffer_Add(simulation->buffer, request));

            break;

        case RELEASE:

            Device*  const d        = e->device;
            Request* const finished = Device_FinishService(d);

            Request_Destroy(finished);

            break;

        default:
            break;
    }

    Event_Destroy(e);

    return true;
}
