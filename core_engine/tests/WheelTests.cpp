#include <gtest/gtest.h>
#include "Wheel.h"
#include "Constants.h"

class WheelVelocityIncreaseTests : public ::testing::TestWithParam<std::pair<float, float>> {};
class WheelVelocityDecreaseTests : public ::testing::TestWithParam<std::pair<float, float>> {};

constexpr float civicBaseTorque{260.31f}; // Base torque for the test
constexpr float deltaTime{0.016f}; // Simulate 60 FPS
constexpr float vehicleMass{CarConstants::MASS_IN_KG}; // Mass of the vehicle in kg

TEST_P(WheelVelocityIncreaseTests, UpdateForwardVelocityIncreasesWithTorque) {
    Wheel baseWheel(25.0f, 10.5f, 25.0f); // Base wheel for comparison
    Wheel wheel(25.0f, 10.5f, 25.0f); // Diameter, width, mass

    float torque{GetParam().first}; // Torque to apply
    float baseTorque{GetParam().second}; // Base torque for comparison
    
    
    float frontWheelWeight{(vehicleMass * PhysicsConstants::GRAVITY * PhysicsConstants::FRONT_WEIGHT_DISTRIBUTION)/2.0f};

    for (int i = 0; i < 100; ++i) {
        wheel.applyTorque(torque, deltaTime,frontWheelWeight,PhysicsConstants::FRICTION_COEFFICIENT);
        baseWheel.applyTorque(baseTorque, deltaTime,frontWheelWeight,PhysicsConstants::FRICTION_COEFFICIENT); // Apply a smaller torque to the base wheel for comparison
    }

    // The forward velocity should increase after applying torque
    std::cout << "Final Angular Velocity: " << wheel.getAngularVelocity() << " rad/s, Base Angular Velocity: " << baseWheel.getAngularVelocity() << " rad/s" << std::endl;
    std::cout << "Final Forward Velocity: " << wheel.getForwardVelocity() << " m/s, Base Forward Velocity: " << baseWheel.getForwardVelocity() << " m/s" << std::endl;
    EXPECT_GT(wheel.getForwardVelocity(), baseWheel.getForwardVelocity());
}

INSTANTIATE_TEST_SUITE_P(
    WheelForwardVelocityTests,
    WheelVelocityIncreaseTests,
    ::testing::Values(
        std::make_pair(civicBaseTorque, 0.0f), // No torque
        std::make_pair(civicBaseTorque * 0.5f, civicBaseTorque * 0.25f), // Half torque
        std::make_pair(civicBaseTorque, 0.0f), // Base torque
        std::make_pair(civicBaseTorque * 1.5f, civicBaseTorque) // Increased torque
    )
);

TEST_P(WheelVelocityDecreaseTests, UpdateForwardVelocityDecreasesWithNegativeTorque) {
    Wheel wheel(25.0f, 10.5f, 25.0f); // Diameter, width, mass
    Wheel baseWheel(25.0f, 10.5f, 25.0f); // Base wheel for comparison

    float torque{GetParam().first}; // Torque to apply
    float baseTorque{GetParam().second}; // Base torque for comparison
    
    float frontWheelWeight{(vehicleMass * PhysicsConstants::GRAVITY * PhysicsConstants::FRONT_WEIGHT_DISTRIBUTION)/2.0f};

    for (int i = 0; i < 100; ++i) {
        wheel.applyTorque(torque, deltaTime,frontWheelWeight,PhysicsConstants::FRICTION_COEFFICIENT);
        baseWheel.applyTorque(baseTorque, deltaTime,frontWheelWeight,PhysicsConstants::FRICTION_COEFFICIENT); // Apply a smaller positive torque to simulate driving force
    }

    EXPECT_LT(wheel.getForwardVelocity(), baseWheel.getForwardVelocity()); // Expect the velocity to be close to zero or negative due to braking
}

INSTANTIATE_TEST_SUITE_P(
    WheelBrakingTests,
    WheelVelocityDecreaseTests,
    ::testing::Values(
        std::make_pair(-civicBaseTorque * 0.5f, civicBaseTorque * 0.25f), // Half braking torque
        std::make_pair(-civicBaseTorque, 0.0f), // Full braking torque
        std::make_pair(-civicBaseTorque * 1.5f, civicBaseTorque), // Increased braking torque
        std::make_pair(civicBaseTorque * 0.25f, civicBaseTorque * 0.5f),
        std::make_pair(civicBaseTorque * 0.5f, civicBaseTorque)
    )
);
