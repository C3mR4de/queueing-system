#include "Listener.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct Listener
{
    int a;
};

Listener* Listener_Create(void)
{
    return malloc(sizeof(Listener));
}

void Listener_Destroy(Listener* const listener)
{
    free(listener);
}

void Listener_OnStep(Listener* const listener, const size_t step, const TimeMoment time, const char* message, Vector* const devices, const Buffer* const buffer)
{
    (void)listener;
    (void)devices;
    (void)buffer;
    printf("Шаг %zu (t = %" PRId32 "): %s\n", step, time, message);
}

void Listener_OnFinish(Listener* const listener)
{
    (void)listener;
    puts("=== Моделирование завершено ===");
}
