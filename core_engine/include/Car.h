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
    float m_vehicleMass;
    float m_vehicleSpeed;
    void updateDashboardUI(float deltaTime);
    void applyTorqueToWheels(float deltaTime);
    void updateEngineRPM(float throttle, float deltaTime);
public:
    Car(float massInKg);
    void update(float throttle, float deltaTime);
};