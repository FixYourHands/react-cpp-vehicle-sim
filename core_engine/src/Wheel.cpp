#include "Wheel.h"
#include <algorithm>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Wheel::Wheel(float diameterInInches, float widthInInches, float massInKg)
	: 
    m_diameter(diameterInInches * PhysicsConstants::INCH_TO_METER), 
    m_width(widthInInches * PhysicsConstants::INCH_TO_METER), 
    m_angularVelocity(0.0f), 
    m_mass(massInKg) 
    {}

float Wheel::getForwardVelocity() const {
	return m_angularVelocity * (m_diameter / 2.0f);
}

float Wheel::getAngularVelocity() const {
    return m_angularVelocity;
}

void Wheel::applyTorque(float engineTorque, float deltaTime, float verticalLoad, float frictionCoefficient) {
    float radius {m_diameter / 2.0f};
    float maxTractionTorque {verticalLoad * frictionCoefficient * radius}; 
    float absEngineTorque {std::abs(engineTorque)};
    float absTraction{std::min(absEngineTorque, maxTractionTorque)};
    float actualTraction{engineTorque >= 0.f ? absTraction : -absTraction}; // Preserve the direction of the torque
    float inertia {0.5f * m_mass * radius * radius}; // Moment of inertia for a solid cylinder

    float netTorque{0.f};
    if (absEngineTorque > maxTractionTorque) {
        netTorque = engineTorque - (maxTractionTorque * (engineTorque > 0 ? 1.0f : -1.0f)); // Full torque is applied if within traction limits
    } else {
        float vehicleInertia{(CarConstants::MASS_IN_KG/2.0f) * radius * radius}; // Approximate inertia of the vehicle's mass on the wheel
        inertia += vehicleInertia; 
        netTorque = engineTorque; 
    }
    float angularAcceleration {netTorque / inertia}; // α = τ / I
    m_angularVelocity += angularAcceleration * deltaTime;
    m_angularVelocity *= PhysicsConstants::VELOCITY_DAMPING_FACTOR; // Simple damping to prevent infinite acceleration
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(wheel_module) {
    emscripten::class_<Wheel>("Wheel")
        .constructor<float, float, float>()
        .function("getForwardVelocity", &Wheel::getForwardVelocity)
        .function("applyTorque", &Wheel::applyTorque)
        .function("getAngularVelocity", &Wheel::getAngularVelocity);
}
#endif