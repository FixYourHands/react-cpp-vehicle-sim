#pragma once

class Tachometer {
private:
    float m_displayedRPM; // Revolutions per minute
    float m_smoothingFactor; // For smoothing RPM changes
    constexpr static float MAX_RPM{8000.0f}; // Maximum RPM for the tachometer
public:
    Tachometer(float smoothingFactor = 10.f);
    void update(float engineRPM, float deltaTime);
    float getDisplayedRPM() const;
};