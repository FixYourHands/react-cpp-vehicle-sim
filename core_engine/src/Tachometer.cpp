#include "Tachometer.h"
#include <emscripten/bind.h>

Tachometer::Tachometer(float smoothingFactor)
    : m_displayedRPM(0.0f), m_smoothingFactor(smoothingFactor) {
}

void Tachometer::update(float engineRPM, float deltaTime) {
    // Smoothly update the displayed RPM using a simple exponential moving average
    m_displayedRPM += (engineRPM - m_displayedRPM) * m_smoothingFactor * deltaTime;

    // Clamp the displayed RPM to the maximum value
    if (m_displayedRPM > MAX_RPM) {
        m_displayedRPM = MAX_RPM;
    }

    if (m_displayedRPM < 0.0f) {
        m_displayedRPM = 0.0f;
    }
}

float Tachometer::getDisplayedRPM() const {
    return m_displayedRPM;
}

EMSCRIPTEN_BINDINGS(tachometer_module) {
    emscripten::class_<Tachometer>("Tachometer")
        .constructor<float>()
        .function("update", &Tachometer::update)
        .function("getDisplayedRPM", &Tachometer::getDisplayedRPM);
}