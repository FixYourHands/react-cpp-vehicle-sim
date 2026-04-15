#include "Wheel.h"
#include <emscripten/bind.h>

Wheel::Wheel(float diameterInInches, float widthInInches, float massInKg)
	: 
    m_diameter(diameterInInches * INCH_TO_METER), 
    m_width(widthInInches * INCH_TO_METER), 
    m_angularVelocity(0.0f), 
    m_mass(massInKg) 
    {}

float Wheel::getForwardVelocity() const {
	return m_angularVelocity * (m_diameter / 2.0f);
}

void Wheel::applyTorque(float torque, float deltaTime) {
    float radius = m_diameter / 2.0f;
    float inertia = 0.5f * m_mass * radius * radius; // Moment of inertia for a solid cylinder
    float angularAcceleration = torque / inertia; // α = τ / I
    m_angularVelocity += angularAcceleration * deltaTime;
    m_angularVelocity *= 0.99f; // Simple damping to prevent infinite acceleration
}

EMSCRIPTEN_BINDINGS(wheel_module) {
    emscripten::class_<Wheel>("Wheel")
        .constructor<float, float, float>()
        .function("getForwardVelocity", &Wheel::getForwardVelocity)
        .function("applyTorque", &Wheel::applyTorque);
}