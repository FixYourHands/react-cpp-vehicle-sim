#include <gtest/gtest.h>
#include "Speedometer.h"

class SpeedometerDisplayedMPHTests : public ::testing::TestWithParam<std::pair<float, float>> {};

TEST_P(SpeedometerDisplayedMPHTests, CalculateMPHReturnsCorrectSpeed) {
    float tireDiameterInInches{25.0f}; // Diameter of the tire in inches
    float wheelAngularVelocity{GetParam().first}; // Angular velocity for the test
    float expectedMPH{GetParam().second}; // Expected MPH for the test

    Speedometer speedometer(tireDiameterInInches);
    float calculatedMPH = speedometer.calculateMPH(wheelAngularVelocity);


    EXPECT_NEAR(calculatedMPH, expectedMPH, 0.01f); // Allow small margin of error
}

INSTANTIATE_TEST_SUITE_P(
    SpeedometerMPHTests,
    SpeedometerDisplayedMPHTests,
    ::testing::Values(
        std::make_pair(0.0f, 0.0f), 
        std::make_pair(10.0f, 7.1f), 
        std::make_pair(20.0f, 14.2f), 
        std::make_pair(50.0f, 35.51f), 
        std::make_pair(100.0f, 71.02f),
        std::make_pair(-10.0f, 7.1f),
        std::make_pair(-20.0f, 14.2f),
        std::make_pair(-50.0f, 35.51f),
        std::make_pair(-100.0f, 71.02f) 
    )
);
