#include "Car.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Car::Car(float massInKg)
    : m_engine(EngineConstants::MAX_TORQUE), 
      m_wheels{ Wheel(WheelConstants::CIVIC_TIRE_DIAMETER_INCHES, WheelConstants::CIVIC_TIRE_WIDTH_INCHES, WheelConstants::CIVIC_TIRE_MASS_KG), 
                Wheel(WheelConstants::CIVIC_TIRE_DIAMETER_INCHES, WheelConstants::CIVIC_TIRE_WIDTH_INCHES, WheelConstants::CIVIC_TIRE_MASS_KG), 
                Wheel(WheelConstants::CIVIC_TIRE_DIAMETER_INCHES, WheelConstants::CIVIC_TIRE_WIDTH_INCHES, WheelConstants::CIVIC_TIRE_MASS_KG), 
                Wheel(WheelConstants::CIVIC_TIRE_DIAMETER_INCHES, WheelConstants::CIVIC_TIRE_WIDTH_INCHES, WheelConstants::CIVIC_TIRE_MASS_KG) },
      m_speedometer(WheelConstants::CIVIC_TIRE_DIAMETER_INCHES),
      m_tachometer(TachometerConstants::SMOOTHING_FACTOR),
      m_transmission(TransmissionConstants::FINAL_DRIVE_RATIO),
      m_fuelTank(FuelConstants::MAX_FUEL_CAPACITY),
      m_vehicleMass(massInKg),
      m_vehicleSpeed(0.0f) {}

void Car::update(float throttle, float deltaTime){
    updateEngineRPM(throttle, deltaTime);
    applyTorqueToWheels(deltaTime);
    updateDashboardUI(deltaTime);
}


void Car::updateEngineRPM(float throttle,float deltaTime){
    m_engine.setThrottleInput(throttle);
    if (m_transmission.isInNeutral()){
        m_engine.update(deltaTime,m_fuelTank,m_transmission);
    }
    else {
        float wheelVelocity {m_wheels[0].getAngularVelocity()};
        float syncedRPM{wheelVelocity * m_transmission.getTotalGearRatio() * PhysicsConstants::ANGULAR_VELOCITY_TO_RPM};
        m_engine.setRPM(syncedRPM);
        m_engine.update(deltaTime,m_fuelTank,m_transmission);
    }
}

void Car::applyTorqueToWheels(float deltaTime){
    float wheelTorque {m_engine.getOutputTorque() * m_transmission.getTotalGearRatio()};
    wheelTorque *= PhysicsConstants::DRIVETRAIN_EFFICIENCY; // Drivetrain efficiency factor
    float torquePerWheel = wheelTorque / 2.0f; // Assuming torque is split between front wheels
    float frontWheelWeight{(m_vehicleMass * PhysicsConstants::GRAVITY * PhysicsConstants::FRONT_WEIGHT_DISTRIBUTION)/2.0f}; // Assuming 60% weight on front wheels
    float frictionCoefficient {PhysicsConstants::FRICTION_COEFFICIENT}; // Typical tire-road friction coefficient
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