#pragma once

static constexpr float INCH_TO_METER = 0.0254f;

class Wheel {
private:
	float m_diameter; // in meters
    float m_width;    // in meters
    float m_angularVelocity; // in radians per second
    float m_mass; // in kilograms
public:
    Wheel(float diameterInInches,float widthInInches, float massInKg = 15.0f);
    float getForwardVelocity() const;
    void applyTorque(float torque, float deltaTime);
};