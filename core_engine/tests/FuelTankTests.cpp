#include <gtest/gtest.h>
#include "FuelTank.h"

class FuelLowTest : public ::testing::TestWithParam<std::pair<int,bool>>{};
class FuelConsumptionTest : public ::testing::TestWithParam<std::pair<int,int>>{};
class FuelRefuelTest : public ::testing::TestWithParam<std::pair<int,int>>{};
class FuelPercentageTest : public ::testing::TestWithParam<std::pair<int,float>>{};


TEST_P(FuelConsumptionTest, ConsumeFuel){
    int consumedFuel = GetParam().first;
    int expectedLevel = GetParam().second;

    FuelTank fuelTank(100);
    fuelTank.consume(consumedFuel);
    EXPECT_EQ(fuelTank.getCurrentLevel(), expectedLevel);
}

INSTANTIATE_TEST_SUITE_P(
    FuelTankConsumptionTests,
    FuelConsumptionTest,
    ::testing::Values(
        std::make_pair(90, 10),
        std::make_pair(100, 0),
        std::make_pair(150, 0),
        std::make_pair(80, 20),
        std::make_pair(0, 100),
        std::make_pair(-25, 100)
    )
);

TEST_P(FuelLowTest, FuelIsLow){
    int consumedFuel = GetParam().first;
    bool expectedLowStatus = GetParam().second;

    FuelTank fuelTank(100);
    fuelTank.consume(consumedFuel);
    EXPECT_EQ(fuelTank.isLow(), expectedLowStatus);
}

INSTANTIATE_TEST_SUITE_P(
    FuelTankLowTests,
    FuelLowTest,
    ::testing::Values(
        std::make_pair(90, true),
        std::make_pair(100, true),
        std::make_pair(80, false),
        std::make_pair(0, false),
        std::make_pair(-25, false)
    )
);

TEST_P(FuelRefuelTest, RefuelFuel){
    int refueledAmount = GetParam().first;
    int expectedLevel = GetParam().second;

    FuelTank fuelTank(100);
    fuelTank.consume(50); // Start at 50% fuel
    fuelTank.refuel(refueledAmount);
    EXPECT_EQ(fuelTank.getCurrentLevel(), expectedLevel);
}

INSTANTIATE_TEST_SUITE_P(
    FuelTankRefuelTests,
    FuelRefuelTest,
    ::testing::Values(
        std::make_pair(20, 70),
        std::make_pair(50, 100),
        std::make_pair(60, 100),
        std::make_pair(0, 50),
        std::make_pair(-25, 50)
    )
);

TEST_P(FuelPercentageTest, FuelPercentage){
    int consumedFuel = GetParam().first;
    float expectedPercentage = GetParam().second;

    FuelTank fuelTank(100);
    fuelTank.consume(consumedFuel);
    EXPECT_FLOAT_EQ(fuelTank.getCurrentPercentage(), expectedPercentage);
}

INSTANTIATE_TEST_SUITE_P(
    FuelTankPercentageTests,
    FuelPercentageTest,
    ::testing::Values(
        std::make_pair(90, 10.0f),
        std::make_pair(100, 0.0f),
        std::make_pair(150, 0.0f),
        std::make_pair(80, 20.0f),
        std::make_pair(0, 100.0f),
        std::make_pair(-25, 100.0f)
    )
);