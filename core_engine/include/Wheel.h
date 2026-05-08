#pragma once
#include "Constants.h"

class Wheel {
private:
	float m_diameter; // in meters
    float m_width;    // in meters
    float m_angularVelocity; // in radians per second
    float m_mass; // in kilograms
public:
    Wheel(float diameterInInches,float widthInInches, float massInKg = WheelConstants::CIVIC_TIRE_MASS_KG);
    float getForwardVelocity() const;
    float getAngularVelocity() const;
    void applyTorque(float torque, float deltaTime, float verticalLoad, float frictionCoefficient);
};