#include "Car.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Car::Car(float massInKg)
    : m_engine(400.f), 
      m_wheels{ Wheel(25.0f, 10.5f, 15.0f), Wheel(25.0f, 10.5f, 15.0f), Wheel(25.0f, 10.5f, 15.0f), Wheel(25.0f, 10.5f, 15.0f) },
      m_speedometer(25.0f),
      m_tachometer(1.f),
      m_transmission(),
      m_fuelTank(1000),
      m_vehicleMass(massInKg),
      m_vehicleSpeed(0.0f) {}

void Car::update(float throttle, float deltaTime){
    updateEngineRPM(throttle, deltaTime);
    applyTorqueToWheels(deltaTime);
    updateDashboardUI(deltaTime);
}


void Car::updateEngineRPM(float throttle,float deltaTime){
    float wheelVelocity {m_wheels[0].getAngularVelocity()};
    float syncedRPM{wheelVelocity * m_transmission.getTotalGearRatio() * (60.0f / 6.28318f)};
    m_engine.setThrottleInput(throttle);
    m_engine.setRPM(syncedRPM);
    m_engine.update(deltaTime,m_fuelTank,m_transmission);
}

void Car::applyTorqueToWheels(float deltaTime){
    float wheelTorque {m_engine.getOutputTorque() * m_transmission.getTotalGearRatio()};
    wheelTorque *= 0.85f; // Drivetrain efficiency factor
    float torquePerWheel = wheelTorque / 2.0f; // Assuming torque is split between front wheels
    float gravity {9.81f};
    float frontWheelWeight{(m_vehicleMass * gravity * 0.6f)/2.0f}; // Assuming 60% weight on front wheels
    float frictionCoefficient {0.9f}; // Typical tire-road friction coefficient
    m_wheels[0].applyTorque(torquePerWheel, deltaTime,frontWheelWeight,frictionCoefficient);
    m_wheels[1].applyTorque(torquePerWheel, deltaTime,frontWheelWeight,frictionCoefficient);
}

void Car::updateDashboardUI(float deltaTime){
    float wheelVelocity {m_wheels[0].getAngularVelocity()};
    m_vehicleSpeed = m_speedometer.calculateMPH(wheelVelocity);
    m_tachometer.update(m_engine.getRPM(), deltaTime);
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(car_module) {
    emscripten::class_<Car>("Car")
        .constructor<float>()
        .function("update", &Car::update);
}
#endif