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


void Engine::update(float throttleInput, float deltaTime, FuelTank& fuelTank, Transmission& transmission){
    if (fuelTank.isEmpty()){
        m_outputTorque = 0.f;
        m_currentRPM -= 500.f * deltaTime;

        m_currentRPM = std::max(0.f,m_currentRPM);
        return;
    }

    int fuelConsumed{static_cast<int>(throttleInput * 10.f * deltaTime)};
    fuelTank.consume(fuelConsumed);

    m_outputTorque = throttleInput * m_maxTorque;

    if (transmission.getCurrentGear() == 0){
        m_currentRPM += (throttleInput * 5000.f - 1000.f) * deltaTime;
    }
    else{
        m_currentRPM += (throttleInput * 2000.f - 500.f) * deltaTime;
    }

    //clamp RPM
    if (m_currentRPM < 800.f) m_currentRPM = 800.f;
    if (m_currentRPM > 8000.f) m_currentRPM = 8000.f;
}

float Engine::getOutputTorque() const{
    return m_outputTorque;
}

float Engine::getRPM() const{
    return m_currentRPM;
}
    
#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(engine_module) {
    emscripten::class_<Engine>("Engine")
        .constructor<float>()
        .function("update", &Engine::update)
        .function("getOutputTorque", &Engine::getOutputTorque)
        .function("getRPM",&Engine::getRPM);
}
#endif