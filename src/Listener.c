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
        puts("Следующее особое событие: конец симуляции");

    const Vector* const sources = Simulation_GetSources(simulation);

    for (size_t i = 0; i < Vector_Size(sources); ++i)
    {
        const Source* const source       = Vector_Get(sources, i);
        const ID            id           = Source_GetID(source);
        const TimeMoment    next_request = Source_GetNextRequestArrivalTime(source);
    
        if (next_request != -1)
            printf("Источник №%" PRIuMAX ": время прибытия следующей заявки t = %" PRIdMAX "\n", id, next_request);
        else
            printf("Источник №%" PRIuMAX ": заявок больше нет\n", id);
    }

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

    if (!next_event)
    {
        puts("================ СТАТИСТИКА ================");
        printf("Вероятность отказа в обслуживании заявок: %.3f%%\n", Simulation_GetDenyProbability(simulation));
        printf("Среднее время пребывания заявок в СМО:    %.3f\n",   Simulation_GetAverageQueueingTime(simulation));
        printf("Коэффициент использования приборов:       %.3f\n",   Simulation_GetDeviceLoadCoefficient(simulation));
    }
}
