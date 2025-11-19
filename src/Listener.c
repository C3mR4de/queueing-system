#include "Listener.h"
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "Event.h"

void Listener_PrintState(const Simulation* const simulation)
{
    assert(simulation);

    const Event* const next_event = PriorityQueue_Peek(Simulation_GetEventQueue(simulation));

    if (next_event)
        printf("Следующее особое событие: %s в момент времени t = %" PRIdMAX "\n", next_event->type == ARRIVAL ? "прибытие заявки" : "освобождение прибора", next_event->time);
    else
        printf("Следующее особое событие: конец симуляции\n");

    const Vector* const devices = Simulation_GetDevices(simulation);

    for (size_t i = 0; i < Vector_Size(devices); ++i)
    {
        const Device* const device       = Vector_Get(devices, i);
        const ID            id           = Device_GetID(device);
        const TimeMoment    release_time = Device_GetPlannedReleaseTime(device);

        if (release_time != -1)
            printf("Прибор №%" PRIuMAX ": время освобождения t = %" PRIdMAX "\n", id, release_time);
        else
            printf("Прибор №%" PRIuMAX ": свободен\n", id);
    }

    const Buffer* const buffer = Simulation_GetBuffer(simulation);

    for (size_t i = 0; i < 2; ++i)
    {
        const Request* const request = Buffer_Get(buffer, i);

        if (!request)
            printf("Элемент буфера №%zu: пустой\n", i);
        else
            printf("Элемент буфера №%zu: время прибытия заявки = %" PRIdMAX "\n", i, request->arrival_time);
    }

    puts("");
}
