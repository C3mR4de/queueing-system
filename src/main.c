#include "Simulation.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_SOURCES  7
#define NUM_DEVICES  5
#define BUFFER_SIZE  4
#define MIN_INTERVAL 15.0
#define MAX_INTERVAL 30.0
#define SERVICE_RATE 0.1
#define MAX_TIME     10000

int main()
{
    Simulation* const simulation = Simulation_Create
    (
        NUM_SOURCES,
        NUM_DEVICES,
        BUFFER_SIZE,
        MIN_INTERVAL,
        MAX_INTERVAL,
        SERVICE_RATE,
        MAX_TIME
    );

    if (!simulation)
        return EXIT_FAILURE;

    while (Simulation_Step(simulation));
    Simulation_Destroy(simulation);

    return EXIT_SUCCESS;
}
