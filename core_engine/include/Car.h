#pragma once
#include "Engine.h"
#include "Wheel.h"
#include "Speedometer.h"
#include "Tachometer.h"
#include "Transmission.h"
#include "FuelTank.h"
#include "Constants.h"
#include <array>

struct CarTelemetryData {
    float speed;
    float wheelAngularVelocity;
    float wheelForwardVelocity;
    float engineRPM;
    float tachometerRPM;
    float currentFuelLevel;
    float fuelRemainingPercentage;
    float rangeInMiles;
    float averageMilesPerGallon;
    int currentGear;
    bool isEngineOn;
    bool isFuelLow;
};

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
    float m_clutchEngagement;
    void updateDashboardUI(float deltaTime);
    void applyTorqueToWheels(float deltaTime);
    void updateEngineRPM(float throttle, float deltaTime);
public:
    Car(float massInKg = CarConstants::MASS_IN_KG);
    void update(float throttle, float deltaTime);
    void toggleEngineStarter();
    void shiftToGear(int gear);
    void setClutchEngagement(float engagement);
    void refuel(float amount);
    void consumeFuel(float amount);
    CarTelemetryData getTelemetryData() const;
};