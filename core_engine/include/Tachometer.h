#pragma once
#include "Constants.h"

class Tachometer {
private:
    float m_displayedRPM; // Revolutions per minute
    float m_smoothingFactor; // For smoothing RPM changes
public:
    Tachometer(float smoothingFactor = TachometerConstants::SMOOTHING_FACTOR);
    void update(float engineRPM, float deltaTime);
    float getDisplayedRPM() const;
};