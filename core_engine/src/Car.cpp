#include "Car.h"
#include <algorithm>

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
      m_vehicleSpeed(0.0f),
      m_clutchEngagement(1.0f)
      {
        if (!m_engine.isRunning()){
            toggleEngineStarter();
        }
      }

void Car::shiftToGear(int gear){
    m_transmission.shiftToGear(gear);
}

void Car::setClutchEngagement(float engagement) {
    m_clutchEngagement = std::clamp(engagement, 0.0f, 1.0f);
}

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
        float currentRPM = m_engine.getRPM();

        if (wheelVelocity < TransmissionConstants::CLUTCH_WHEEL_ANGULAR_VELOCITY_THRESHOLD && throttle > 0.0f) {
            // Clutch is slipping: hold RPM near the launch target while wheels are still nearly stopped.
            float maxLaunchRPM = EngineConstants::LAUNCH_RPM + (1.0f - m_clutchEngagement) * EngineConstants::LAUNCH_RPM;
            float dynamicFriction{EngineConstants::RPM_DECREASE_RATE + (currentRPM * 0.1f)};
            float rpmChange{(throttle * EngineConstants::RPM_INCREASE_RATE - dynamicFriction) * deltaTime};
            float nextRPM{std::clamp(currentRPM + rpmChange, EngineConstants::IDLE_RPM, maxLaunchRPM)};
            m_engine.setRPM(nextRPM);
        }
        else {
            float syncedRPM{wheelVelocity * m_transmission.getTotalGearRatio() * PhysicsConstants::ANGULAR_VELOCITY_TO_RPM};
            // Blend engine RPM toward the wheel-synced RPM to simulate clutch engagement/slip.
            float blendAlpha = std::clamp(TransmissionConstants::CLUTCH_BLEND_RATE * m_clutchEngagement * deltaTime, 0.0f, 1.0f);
            float blendedRPM = currentRPM + (syncedRPM - currentRPM) * blendAlpha;
            m_engine.setRPM(blendedRPM);
        }

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

void Car::toggleEngineStarter(){
    if (m_engine.isRunning()){
        m_engine.stopEngine();
    }
    else {
        m_engine.startEngine(m_fuelTank);
    }
}

CarTelemetryData Car::getTelemetryData() const {
    CarTelemetryData data;
    data.speed = m_vehicleSpeed;
    data.wheelAngularVelocity = m_wheels[0].getAngularVelocity();
    data.wheelForwardVelocity = m_wheels[0].getForwardVelocity();
    data.engineRPM = m_engine.getRPM();
    data.tachometerRPM = m_tachometer.getDisplayedRPM();
    data.currentFuelLevel = m_fuelTank.getCurrentLevel();
    data.fuelRemainingPercentage = m_fuelTank.getCurrentPercentage();
    data.currentGear = m_transmission.getCurrentGear();
    data.isEngineOn = m_engine.isRunning();
    data.isFuelLow = m_fuelTank.isLow();
    return data;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(car_module) {
    emscripten::class_<Car>("Car")
        .constructor<float>()
        .function("update", &Car::update)
        .function("getTelemetryData", &Car::getTelemetryData)
        .function("toggleEngineStarter", &Car::toggleEngineStarter)
        .function("shiftToGear", &Car::shiftToGear)
        .function("setClutchEngagement", &Car::setClutchEngagement);
}
#endif