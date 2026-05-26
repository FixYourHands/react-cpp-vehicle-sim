#include <gtest/gtest.h>
#include "FuelTank.h"

class FuelLowTest : public ::testing::TestWithParam<std::pair<int,bool>>{};
class FuelConsumptionTest : public ::testing::TestWithParam<std::pair<int,int>>{};
class FuelRefuelTest : public ::testing::TestWithParam<std::pair<int,int>>{};
class FuelPercentageTest : public ::testing::TestWithParam<std::pair<int,float>>{};


TEST_P(FuelConsumptionTest, ConsumeFuel){
    float consumedFuel = GetParam().first;
    float expectedLevel = GetParam().second;

    FuelTank fuelTank(100);
    fuelTank.consume(consumedFuel);
    EXPECT_EQ(fuelTank.getCurrentLevel(), expectedLevel);
}

INSTANTIATE_TEST_SUITE_P(
    FuelTankConsumptionTests,
    FuelConsumptionTest,
    ::testing::Values(
        std::make_pair(90.0f, 10.0f),
        std::make_pair(100.0f, 0.0f),
        std::make_pair(150.0f, 0.0f),
        std::make_pair(80.0f, 20.0f),
        std::make_pair(0.0f, 100.0f),
        std::make_pair(-25.0f, 100.0f)
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
        std::make_pair(90.0f, true),
        std::make_pair(100.0f, true),
        std::make_pair(80.0f, false),
        std::make_pair(0.0f, false),
        std::make_pair(-25.0f, false)
    )
);

TEST_P(FuelRefuelTest, RefuelFuel){
    float refueledAmount = GetParam().first;
    float expectedLevel = GetParam().second;

    FuelTank fuelTank(100);
    fuelTank.consume(50.0f); // Start at 50% fuel
    fuelTank.refuel(refueledAmount);
    EXPECT_EQ(fuelTank.getCurrentLevel(), expectedLevel);
}

INSTANTIATE_TEST_SUITE_P(
    FuelTankRefuelTests,
    FuelRefuelTest,
    ::testing::Values(
        std::make_pair(20.0f, 70.0f),
        std::make_pair(50.0f, 100.0f),
        std::make_pair(60.0f, 100.0f),
        std::make_pair(0.0f, 50.0f),
        std::make_pair(-25.0f, 50.0f)
    )
);

TEST_P(FuelPercentageTest, FuelPercentage){
    float consumedFuel = GetParam().first;
    float expectedPercentage = GetParam().second;

    FuelTank fuelTank(100);
    fuelTank.consume(consumedFuel);
    EXPECT_FLOAT_EQ(fuelTank.getCurrentPercentage(), expectedPercentage);
}

INSTANTIATE_TEST_SUITE_P(
    FuelTankPercentageTests,
    FuelPercentageTest,
    ::testing::Values(
        std::make_pair(90.0f, 10.0f),
        std::make_pair(100.0f, 0.0f),
        std::make_pair(150.0f, 0.0f),
        std::make_pair(80.0f, 20.0f),
        std::make_pair(0.0f, 100.0f),
        std::make_pair(-25.0f, 100.0f)
    )
);