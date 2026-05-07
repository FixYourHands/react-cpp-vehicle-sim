#include <gtest/gtest.h>
#include "Tachometer.h"

TEST(TachometerTests, UpdateSmoothlyIncreasesDisplayedRPM) {
    Tachometer tachometer(1.f); 
    float targetRPM{4000.0f};
    float deltaTime{0.016f}; // Simulate 60 FPS

    for (int i = 0; i < 1000; ++i) {
        tachometer.update(targetRPM, deltaTime);
    }

    // The displayed RPM should be close to the target RPM after multiple updates
    EXPECT_NEAR(tachometer.getDisplayedRPM(), 4000.0f, 10.f);
}

TEST(TachometerTests, UpdateDoesNotExceedMaxRPM) {
    Tachometer tachometer(1.f); 
    float targetRPM{10000.0f}; // Exceeds MAX_RPM
    float deltaTime{0.016f}; // Simulate 60 FPS

    for (int i = 0; i < 1000; ++i) {
        tachometer.update(targetRPM, deltaTime);
    }

    // The displayed RPM should not exceed the maximum RPM
    EXPECT_LE(tachometer.getDisplayedRPM(), 8000.0f);
}

TEST(TachometerTests, UpdateDoesNotGoBelowZero) {
    Tachometer tachometer(1.f); 
    float targetRPM{-1000.0f}; // Negative RPM
    float deltaTime{0.016f}; // Simulate 60 FPS

    for (int i = 0; i < 1000; ++i) {
        tachometer.update(targetRPM, deltaTime);
    }

    // The displayed RPM should not go below zero
    EXPECT_GE(tachometer.getDisplayedRPM(), 0.0f);
}