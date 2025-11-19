#include "Simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Listener.h"
#include "Event.h"
#include "PriorityQueue.h"

struct Simulation
{
    Vector*        const sources;
    Vector*        const devices;
    Buffer*        const buffer;
    PriorityQueue* const event_queue;
    MT19937              random;

    size_t     step_counter;
    TimeMoment current_time;
    TimeMoment max_time;
    double     service_rate;
};

static bool __Simulation_CompareEvents(const void* const lhs, const void* const rhs)
{
    if (!lhs)
        return false;

    if (!rhs)
        return true;

    return ((Event*)lhs)->time < ((Event*)rhs)->time;
}

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
        .event_queue  = PriorityQueue_Create(10 * num_sources, __Simulation_CompareEvents),
        .random       = MT19937_Create(time(NULL) / 4),
        .step_counter = 0,
        .current_time = 0,
        .max_time     = max_time,
        .service_rate = service_rate,
    };

    if (!(tmp.sources && tmp.devices && tmp.buffer && tmp.event_queue))
        goto cleanup;

    for (size_t i = 0; i < num_sources; ++i)
    {
        Source* const add_source = Source_Create(i + 1, min_interval, max_interval);

        if (!add_source)
            goto cleanup;

        Vector_Set(tmp.sources, i, add_source);
    }

    for (size_t i = 0; i < num_devices; ++i)
    {
        Device* const add_device = Device_Create(i + 1);

        if (!add_device)
            goto cleanup;

        Vector_Set(tmp.devices, i, add_device);
    }

    TimeMoment latest_moment[SOURCE_REQUESTS_COUNT];
    memset(latest_moment, 0, sizeof(latest_moment));

    for (size_t i = 0; i < num_sources; ++i)
    {
        Source* const s = Vector_Get(tmp.sources, i);

        for (size_t j = 0; j < SOURCE_REQUESTS_COUNT; ++j)
        {
            latest_moment[i] += (TimeMoment)Source_GenerateArrivalInterval(s);
            TimeMoment const t = latest_moment[i];
            Source_GetRequestsArrival(s)[j] = t;

            printf("Генерация заявки на источнике №%zu... Время %" PRIdMAX "\n", i, t);

            PriorityQueue_Enqueue(tmp.event_queue, Event_Create(ARRIVAL, t, (EventRelative){ .source = s }));
        }
    }

    puts("");

    memcpy(simulation, &tmp, sizeof(Simulation));
    return simulation;

cleanup:

    Simulation_Destroy(&tmp);
    return NULL;
}

void Simulation_Destroy(Simulation* const simulation)
{
    assert(simulation);

    while (!PriorityQueue_IsEmpty(simulation->event_queue))
        Event_Destroy(PriorityQueue_Dequeue(simulation->event_queue));

    PriorityQueue_Destroy(simulation->event_queue);

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

    Event* const e = PriorityQueue_Dequeue(simulation->event_queue);

    if (!e)
        return false;

    simulation->current_time = e->time;
    ++simulation->step_counter;

    printf("Шаг №%zu\n", simulation->step_counter);

    switch (e->type)
    {
        case ARRIVAL:
            {
                Request* const request = Source_GenerateRequest(e->relative.source, simulation->current_time);
                Device*  const device  = Dispatcher_SelectDevice(simulation->devices);

                Source_ArriveRequest(e->relative.source);

                if (device)
                {
                    const TimeMoment service_time = MT19937_RandRange(&simulation->random, 30, 40);

                    Device_StartService(device, request, simulation->current_time, service_time);
                    PriorityQueue_Enqueue(simulation->event_queue, Event_Create(RELEASE, simulation->current_time + service_time, (EventRelative){ .device = device }));

                    printf("t = %" PRIdMAX ": Начало обслуживания заявки с источника №%" PRIuMAX " на приборе №%" PRIuMAX "\n", simulation->current_time, request->source_id, Device_GetID(device));
                    printf("Длительность обслуживания t = %" PRIdMAX "\n", service_time);
                }
                else
                {
                    printf("t = %" PRIdMAX ": Постановка в буфер заявки c источника №%" PRIuMAX "\n", simulation->current_time, request->source_id);

                    Request* const denied_request = Buffer_Add(simulation->buffer, request);
                    
                    if (denied_request)
                    {
                        printf("Отказано заявке с временем поступления в буфер t = %" PRIdMAX "\n", denied_request->arrival_time);
                        Request_Destroy(denied_request);
                    }
                }
            }
            break;

        case RELEASE:
            {
                Device*  const d        = e->relative.device;
                Request* const finished = Device_FinishService(d);

                Request_Destroy(finished);

                Request* from_buffer = Buffer_Poll(simulation->buffer);

                if (from_buffer)
                {
                    const TimeMoment service_time = MT19937_RandRange(&simulation->random, 5, 20);

                    Device_StartService(d, from_buffer, simulation->current_time, service_time);
                    PriorityQueue_Enqueue(simulation->event_queue, Event_Create(RELEASE, simulation->current_time + service_time, (EventRelative){.device = d }));

                    printf("t = %" PRIdMAX ": Начало обслуживания заявки из буфера на приборе №%" PRIuMAX "\n", simulation->current_time, Device_GetID(d));
                    printf("Длительность обслуживания t = %" PRIdMAX "\n", service_time);
                }
                else
                    printf("t = %" PRIdMAX ": Освобождён и отправлен в простой прибор №%" PRIuMAX "\n", simulation->current_time, Device_GetID(d));
            }
            break;

        default:
            break;
    }

    Event_Destroy(e);
    Listener_PrintState(simulation);

    return true;
}

const Vector* Simulation_GetSources(const Simulation* simulation)
{
    assert(simulation);
    return simulation->sources;
}

const Vector* Simulation_GetDevices(const Simulation* const simulation)
{
    assert(simulation);
    return simulation->devices;
}

const Buffer* Simulation_GetBuffer(const Simulation* const simulation)
{
    assert(simulation);
    return simulation->buffer;
}

const PriorityQueue* Simulation_GetEventQueue(const Simulation* simulation)
{
    assert(simulation);
    return simulation->event_queue;
}
