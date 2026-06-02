#include <gtest/gtest.h>
#include "Car.h"

TEST(CarTest, EngineStartsWithDefaultConstructor) {
    Car car;
    CarTelemetryData telemetry = car.getTelemetryData();
    EXPECT_TRUE(telemetry.isEngineOn);
}

TEST(CarTests, CarStartsInNeutral) {
    Car car;
    CarTelemetryData telemetry = car.getTelemetryData();
    EXPECT_EQ(telemetry.currentGear, 0);
}

TEST(CarTest, EngineStateCanBeToggled) {
    Car car;
    car.toggleEngineStarter(); // Should stop the engine
    CarTelemetryData telemetry = car.getTelemetryData();
    EXPECT_FALSE(telemetry.isEngineOn);
    
    car.toggleEngineStarter(); // Should start the engine again
    telemetry = car.getTelemetryData();
    EXPECT_TRUE(telemetry.isEngineOn);
}

TEST(CarTest, ThrottleApplication) {
    Car car;
    car.shiftToGear(1); 
    
    for (int i = 0; i < 300; ++i) {
        car.update(1.0f, 0.016f); // Full throttle, simulating 60 FPS
    }
    CarTelemetryData telemetry = car.getTelemetryData();
    std::cout << "Speed: " << telemetry.speed << " MPH, Engine RPM: " << telemetry.engineRPM << " RPM" << std::endl;
    EXPECT_GT(telemetry.engineRPM, 0); // Engine RPM should be greater than 0
    EXPECT_GT(telemetry.speed, 0); // Vehicle speed should be greater than 0
    EXPECT_GT(telemetry.wheelAngularVelocity, 0); 
    EXPECT_GT(telemetry.wheelForwardVelocity, 0); 
}