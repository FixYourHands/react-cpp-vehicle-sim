#include "Speedometer.h"
#include "Constants.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Speedometer::Speedometer(float tireDiameterInInches)
    : m_tireDiameterInInches(tireDiameterInInches)
{
}

float Speedometer::calculateMPH(float wheelAngularVelocity) const
{
    // Convert tire diameter from inches to meters
    float radiusInMeters { (m_tireDiameterInInches * PhysicsConstants::INCH_TO_METER) / 2.0f };

    // Calculate the linear velocity in meters per second
    float linearVelocity {std::abs(wheelAngularVelocity) * radiusInMeters}; // v = ω * r

    // Convert linear velocity from meters per second to miles per hour
    float mph{linearVelocity * PhysicsConstants::METERS_PER_SECOND_TO_MPH}; // 1 m/s = 2.23694 mph

    return mph;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(speedometer_module) {
    emscripten::class_<Speedometer>("Speedometer")
        .constructor<float>()
        .function("getSpeed", &Speedometer::calculateMPH);
}
#endif