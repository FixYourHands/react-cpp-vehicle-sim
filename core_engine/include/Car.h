#pragma once
#include "Engine.h"
#include "Wheel.h"
#include "Speedometer.h"
#include "Tachometer.h"
#include "Transmission.h"
#include "FuelTank.h"
#include <array>

class Car{
private:
    Engine m_engine;
    std::array<Wheel, 4> m_wheels;
    Speedometer m_speedometer;
    Tachometer m_tachometer;
    Transmission m_transmission;
    FuelTank m_fuelTank;
public:
}