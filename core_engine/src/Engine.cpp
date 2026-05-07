#include "Engine.h"
#include <algorithm>
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Engine::Engine(float maxTorque)
    :
    m_maxTorque(maxTorque),
    m_currentRPM(0.f),
    m_outputTorque(0.f){}


float Engine::calculateTorqueMultiplier() const{
    float torqueMultipler{1.f};
    if (m_currentRPM < 2500.f){
        torqueMultipler = m_currentRPM / 3500.f; 
    }
    else if (m_currentRPM > 4500.f){
        torqueMultipler = 1.f - (m_currentRPM - 4500.f) / 3500.f;
    }
    return torqueMultipler;
}

void Engine::update(float deltaTime, FuelTank& fuelTank, Transmission& transmission){
    if (fuelTank.isEmpty()){
        m_outputTorque = 0.f;
        m_currentRPM -= 500.f * deltaTime;

        m_currentRPM = std::max(0.f,m_currentRPM);
        return;
    }

    int fuelConsumed{static_cast<int>(m_throttleInput * 10.f * deltaTime)};
    fuelTank.consume(fuelConsumed);

    m_outputTorque = m_throttleInput * m_maxTorque * calculateTorqueMultiplier();

    if (transmission.isInNeutral()){
        m_currentRPM += (m_throttleInput * 5000.f - 1000.f) * deltaTime;
    }

    m_currentRPM = std::clamp(m_currentRPM, 800.f, 8000.f);
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
    m_currentRPM = std::clamp(rpm, 0.f, 8000.f);
}
    
#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(engine_module) {
    emscripten::class_<Engine>("Engine")
        .constructor<float>()
        .function("update", &Engine::update)
        .function("getOutputTorque", &Engine::getOutputTorque)
        .function("getRPM",&Engine::getRPM);
        .function("setThrottleInput", &Engine::setThrottleInput);
        .function("setRPM", &Engine::setRPM);
}
#endif