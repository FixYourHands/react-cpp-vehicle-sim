#include "Car.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

void Car::update(float throttle, float deltaTime){
    m_engine.update(throttle,deltaTime,m_fuelTank,m_transmission);
    float currentRPM = m_engine.getRPM();

    m_tachometer.update(currentRPM, deltaTime);

    float wheelVelocity = m_wheels[0].getForwardVelocity();
    float currentMPH = m_speedometer.calculateMPH(wheelVelocity);

    float torque = m_engine.getOutputTorque() * m_transmission.getCurrentGearRatio();
    for (auto& w: m_wheels){
        w.applyTorque(torque,deltaTime);
    }
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(car_module) {
    emscripten::class_<Car>("Car")
        .function("update", &Car::update);
}
#endif