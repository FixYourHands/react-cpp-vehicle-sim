#include "Speedometer.h"
#include <emscripten/bind.h>

Speedometer::Speedometer(float tireDiameterInInches)
    : m_tireDiameterInInches(tireDiameterInInches)
{
}

float Speedometer::calculateMPH(float wheelAngularVelocity) const
{
    // Convert tire diameter from inches to meters
    float radiusInMeters = (m_tireDiameterInInches * INCH_TO_METER) / 2.0f;

    // Calculate the linear velocity in meters per second
    float linearVelocity = wheelAngularVelocity * radiusInMeters; // v = ω * r

    // Convert linear velocity from meters per second to miles per hour
    float mph = linearVelocity * 2.23694f; // 1 m/s = 2.23694 mph

    return mph;
}

EMSCRIPTEN_BINDINGS(speedometer_module) {
    emscripten::class_<Speedometer>("Speedometer")
        .constructor<float>()
        .function("getSpeed", &Speedometer::calculateMPH);
}