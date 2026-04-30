#include <gtest/gtest.h>
#include "FuelTank.h"

TEST(FuelTankTests, ConsumeFuel){
    FuelTank fuelTank(100);
    fuelTank.consume(30);
    EXPECT_EQ(fuelTank.getCurrentLevel(), 70);
}

TEST(FuelTankTests, FuelIsLow){
    FuelTank fuelTank(100);
    fuelTank.consume(85);
    EXPECT_TRUE(fuelTank.isLow());
}