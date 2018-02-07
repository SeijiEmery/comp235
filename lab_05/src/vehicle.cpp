#include "vehicle.h"

Vehicle::Vehicle (int wheels)
    : m_wheels(wheels)
{
    ++totalVehicles;
}

int Vehicle::totalVehicles = 0;
int Vehicle::howManyVehicles () {
    return totalVehicles;
}
