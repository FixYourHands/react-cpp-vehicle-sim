#include "Wheel.h"
#include <algorithm>
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

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

float Wheel::getAngularVelocity() const {
    return m_angularVelocity;
}

void Wheel::applyTorque(float engineTorque, float deltaTime, float verticalLoad, float frictionCoefficient) {
    float radius {m_diameter / 2.0f};
    float tractionTorque{frictionCoefficient * verticalLoad * radius};
    float actualTraction {std::min(engineTorque, tractionTorque)};

    if (engineTorque < 0) {
        actualTraction *= -1.0f; // Reverse direction for braking
    }
    float inertia {0.5f * m_mass * radius * radius}; // Moment of inertia for a solid cylinder
    float netTorque {engineTorque - actualTraction};
    float angularAcceleration {netTorque / inertia}; // α = τ / I
    m_angularVelocity += angularAcceleration * deltaTime;
    m_angularVelocity *= 0.99f; // Simple damping to prevent infinite acceleration
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(wheel_module) {
    emscripten::class_<Wheel>("Wheel")
        .constructor<float, float, float>()
        .function("getForwardVelocity", &Wheel::getForwardVelocity)
        .function("applyTorque", &Wheel::applyTorque);
        .function("getAngularVelocity", &Wheel::getAngularVelocity);
}
#endif