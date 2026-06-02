#include "Engine.h"
#include <algorithm>
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Engine::Engine(float maxTorque)
    :
    m_maxTorque(maxTorque),
    m_currentRPM(0.f),
    m_outputTorque(0.f),
    m_isRunning(true) {
}

bool Engine::isRunning() const {
    return m_isRunning;
}

void Engine::startEngine(const FuelTank& fuelTank) {
    if (fuelTank.isEmpty()) {
        stopEngine();
        return;
    }
    m_isRunning = true;
}

void Engine::stopEngine() {
    m_isRunning = false;
}

float Engine::calculateTorqueMultiplier() const{
    float torqueMultipler{1.f};
    if (m_currentRPM < EngineConstants::TORQUE_CURVE_LOW_THRESHOLD){
        torqueMultipler = m_currentRPM / EngineConstants::TORQUE_CURVE_FALLOFF_RATE; 
    }
    else if (m_currentRPM > EngineConstants::TORQUE_CURVE_HIGH_THRESHOLD){
        torqueMultipler = 1.f - (m_currentRPM - EngineConstants::TORQUE_CURVE_HIGH_THRESHOLD) / EngineConstants::TORQUE_CURVE_FALLOFF_RATE;
    }
    return std::clamp(torqueMultipler, 0.f, 1.f);
}

void Engine::update(float deltaTime, FuelTank& fuelTank, Transmission& transmission){
    if (fuelTank.isEmpty()){
        stopEngine();
        m_outputTorque = 0.f;
        m_currentRPM -= EngineConstants::ENGINE_FRICTION_DECAY_RATE * deltaTime;
        m_currentRPM = std::max(0.f,m_currentRPM);
        return;
    }
    float rotationalFuelConsumption{m_currentRPM * FuelConstants::FUEL_CONSUMPTION_RATE_INCREASE_PER_RPM};
    float loadFuelConsumption{m_throttleInput * FuelConstants::THROTTLE_FUEL_FACTOR * (m_currentRPM / EngineConstants::MAX_RPM)};

    float fuelConsumed{rotationalFuelConsumption + loadFuelConsumption + FuelConstants::BASE_FUEL_CONSUMPTION_RATE};
    fuelConsumed *= deltaTime; // Scale by deltaTime to get fuel consumed in this update
    fuelTank.consume(fuelConsumed);

    m_outputTorque = m_throttleInput * m_maxTorque * calculateTorqueMultiplier();

    if (transmission.isInNeutral()){
        float dynamicFriction{EngineConstants::RPM_DECREASE_RATE + (m_currentRPM * .1f)};
        m_currentRPM += (m_throttleInput * EngineConstants::RPM_INCREASE_RATE - dynamicFriction) * deltaTime;
        m_currentRPM = std::clamp(m_currentRPM, EngineConstants::IDLE_RPM, EngineConstants::MAX_RPM);
    }
    else {
        m_currentRPM = std::clamp(m_currentRPM, 0.f, EngineConstants::MAX_RPM);
    }
}

void Engine::setThrottleInput(float throttleInput){
    m_throttleInput = std::clamp(throttleInput, 0.f, 1.f);
}

float Engine::getOutputTorque() const{
    return m_outputTorque;
}

float Engine::getRPM() const{
    return m_currentRPM;
}

void Engine::setRPM(float rpm){
    m_currentRPM = std::clamp(rpm, 0.f, EngineConstants::MAX_RPM);
}
    
#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(engine_module) {
    emscripten::class_<Engine>("Engine")
        .constructor<float>()
        .function("update", &Engine::update)
        .function("getOutputTorque", &Engine::getOutputTorque)
        .function("getRPM",&Engine::getRPM)
        .function("setThrottleInput", &Engine::setThrottleInput)
        .function("setRPM", &Engine::setRPM)
        .function("isRunning", &Engine::isRunning)
        .function("startEngine", &Engine::startEngine)
        .function("stopEngine", &Engine::stopEngine);
}
#endif