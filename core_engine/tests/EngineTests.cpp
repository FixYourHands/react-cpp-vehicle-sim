#include <gtest/gtest.h>
#include "Engine.h"
#include "Transmission.h"
#include "FuelTank.h"
#include "Constants.h"



TEST(EngineTests, RPMDoesNotExceedMaxRPM) {
    float maxRPM{EngineConstants::MAX_RPM};
    Engine engine(EngineConstants::MAX_TORQUE);
    engine.setRPM(maxRPM + 1000.f); // Attempt to set RPM above the maximum

    EXPECT_EQ(engine.getRPM(), maxRPM); // Initial RPM should be 0
}

TEST(EngineTests, RPMDoesNotGoBelowZero) {
    Engine engine(EngineConstants::MAX_TORQUE);
    engine.setRPM(4000.f-6000.f); // Attempt to set RPM below zero

    EXPECT_EQ(engine.getRPM(), 0.f);
}

TEST(EngineTests, OutputTorqueIsZeroWhenFuelTankIsEmpty) {
    Engine engine(EngineConstants::MAX_TORQUE);
    FuelTank fuelTank;
    fuelTank.consume(FuelConstants::MAX_FUEL_CAPACITY); // Empty the fuel tank
    Transmission transmission;

    engine.setThrottleInput(1.0f); // Full throttle
    for (int i = 0; i < 100; ++i) {
        engine.update(0.016f, fuelTank, transmission); // Update the engine multiple times to simulate time passing
    }

    EXPECT_EQ(engine.getOutputTorque(), 0.f); // Output torque should be zero when fuel tank is empty
}

TEST(EngineTests, FuelConsumptionWithZeroThrottle) {
    Engine engine(EngineConstants::MAX_TORQUE);
    FuelTank fuelTank;
    Transmission transmission;
    float baseRate{FuelConstants::BASE_FUEL_CONSUMPTION_RATE};

    float initialFuelLevel{fuelTank.getCurrentLevel()};

    engine.setThrottleInput(0.0f); // No throttle
    for (int i = 0; i < 5000; ++i) {
        engine.update(0.016f, fuelTank, transmission); // Update the engine multiple times to simulate time passing
    }

    EXPECT_NEAR(fuelTank.getCurrentLevel(), initialFuelLevel, 2.0f); // Fuel level should not change with zero throttle

}

TEST(EngineTests, FuelConsumptionWithNoThrottleAtHighRPM) {
    Engine engine(EngineConstants::MAX_TORQUE);
    FuelTank fuelTank;
    Transmission transmission;
    float baseRate{FuelConstants::BASE_FUEL_CONSUMPTION_RATE};

    float initialFuelLevel{fuelTank.getCurrentLevel()};

    engine.setRPM(4000.f); // Set RPM to a high value
    engine.setThrottleInput(0.0f); // No throttle
    for (int i = 0; i < 1000; ++i) {
        engine.update(0.016f, fuelTank, transmission); // Update the engine multiple times to simulate time passing
    }

    float currentFuelLevel{fuelTank.getCurrentLevel()};
    EXPECT_LT(currentFuelLevel, initialFuelLevel); 
    float fuelConsumed{initialFuelLevel - fuelTank.getCurrentLevel()};

    engine.setRPM(8000.f);

    for (int i = 0; i < 1000; ++i) {
        engine.update(0.016f, fuelTank, transmission); // Update the engine multiple times to simulate time passing
    }
    float fuelConsumedAt8000RPM{currentFuelLevel - fuelTank.getCurrentLevel()};

    EXPECT_GT(fuelConsumedAt8000RPM, fuelConsumed); 
}

TEST(EngineTests, FuelConsumptionWithVariableThrottle){
    Engine engine(EngineConstants::MAX_TORQUE);
    FuelTank fuelTank;

    Transmission transmission;

    float diff[5]{0.f, 0.f, 0.f, 0.f, 0.f};
    float throttleLevels[5] = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    float currentLevel{fuelTank.getCurrentLevel()};

    for (int i = 0; i < 5; ++i) {
        engine.setThrottleInput(throttleLevels[i]);
        for (int j = 0; j < 5000; ++j) {
            engine.update(0.016f, fuelTank, transmission); // Update the engine multiple times to simulate time passing
        }
        float newLevel{fuelTank.getCurrentLevel()};
        diff[i] = currentLevel - newLevel;
        currentLevel = newLevel;
    }


    EXPECT_GT(diff[1], diff[0]);
    EXPECT_GT(diff[2], diff[1]);
    EXPECT_GT(diff[3], diff[2]);
    EXPECT_GT(diff[4], diff[3]);
}

TEST(EngineTests, NeutralRPMBehavior) {
    Engine engine(EngineConstants::MAX_TORQUE);
    float peakRPM{0.f};
    Transmission transmission;
    transmission.shiftToGear(0); // Set to fifth gear to allow RPM to increase with throttle
    FuelTank fuelTank;
    int counter[5]{0, 0, 0, 0, 0};
    float throttleLevels[5] = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};

    for (int i = 0; i < 5; ++i) {
        engine.setThrottleInput(throttleLevels[i]);
        for (int j = 0; j < 5000; ++j) {
            engine.update(0.016f, fuelTank, transmission); // Update the engine multiple times to simulate time passing
            if (engine.getRPM() >= 4000.f) {
                break;
            }
            counter[i]++;
        }
        float currentRPM{engine.getRPM()};
        if (currentRPM > peakRPM) {
            peakRPM = currentRPM;
        }
        engine.setRPM(0.f); 
    }

    

    EXPECT_GT(peakRPM, 0.f); // Peak RPM should be greater than zero
    EXPECT_LE(peakRPM, EngineConstants::MAX_RPM);
    EXPECT_LE(counter[1], counter[0]);
    EXPECT_LE(counter[2], counter[1]);
    EXPECT_LE(counter[3], counter[2]);
    EXPECT_LE(counter[4], counter[3]); 
}

TEST(EngineTests, RPMDecayWhileIdling) {
    Engine engine(EngineConstants::MAX_TORQUE);
    FuelTank fuelTank;
    Transmission transmission;

    engine.setThrottleInput(0.0f); // No throttle
    engine.setRPM(3000.f); // Set initial RPM above idle
    std::cout << "Initial RPM: " << engine.getRPM() << std::endl;
    for (int i = 0; i < 1000; ++i) {
        engine.update(0.016f, fuelTank, transmission); // Update the engine multiple times to simulate time passing
    }

    std::cout << "Final RPM after idling: " << engine.getRPM() << std::endl;
    EXPECT_NEAR(engine.getRPM(), EngineConstants::IDLE_RPM, 50.f); // RPM should decay towards idle RPM when not throttled
}

TEST(EngineTests, EngineStopsWhenFuelRunsOut) {
    Engine engine(EngineConstants::MAX_TORQUE);
    FuelTank fuelTank;
    Transmission transmission;

    EXPECT_TRUE(engine.isRunning()); // Engine should be running initially

    engine.setThrottleInput(1.0f); // Full throttle
    for (int i = 0; i < 1000; ++i) {
        fuelTank.consume(10);
        engine.update(0.016f, fuelTank, transmission);

    }

    EXPECT_TRUE(fuelTank.isEmpty()); // Fuel tank should be empty
    EXPECT_EQ(engine.getOutputTorque(), 0.f); 
    EXPECT_FALSE(engine.isRunning()); 
}

TEST(EngineTests, RPMDecreasesWhenEngineStopsDueToNoFuel) {
    Engine engine(EngineConstants::MAX_TORQUE);
    FuelTank fuelTank;
    Transmission transmission;

    engine.setThrottleInput(1.0f); // Full throttle
    for (int i = 0; i < 100; ++i) {
        fuelTank.consume(10);
        engine.update(0.016f, fuelTank, transmission);
    }

    EXPECT_TRUE(fuelTank.isEmpty()); // Fuel tank should be empty
    EXPECT_FALSE(engine.isRunning()); // Engine should have stopped

    float rpmAfterStop{engine.getRPM()};
    for (int i = 0; i < 1000; ++i) {
        engine.update(0.016f, fuelTank, transmission);
    }

    EXPECT_LT(engine.getRPM(), rpmAfterStop);
    EXPECT_EQ(engine.getRPM(),0.f); 
}

