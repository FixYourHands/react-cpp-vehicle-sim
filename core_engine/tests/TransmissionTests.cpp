#include <gtest/gtest.h>
#include "Transmission.h"

class GearRatioTests : public ::testing::TestWithParam<std::pair<int, float>> {};

TEST(TransmissionTests, InitialGearIsNeutral) {
    Transmission transmission;
    EXPECT_EQ(transmission.isInNeutral(), true); // Neutral
}

TEST(TransmissionTests, ShiftToGearWorks) {
    Transmission transmission;
    transmission.shiftToGear(3);
    EXPECT_EQ(transmission.getCurrentGear(), 3); // Third

    transmission.shiftToGear(0);
    EXPECT_EQ(transmission.isInNeutral(), true); // Neutral

    transmission.shiftToGear(7); // Invalid
    EXPECT_EQ(transmission.getCurrentGear(), 0); // Should still be Neutral
    EXPECT_EQ(transmission.isInNeutral(), true);
}

TEST(TransmissionTests, UpshiftWorks) {
    Transmission transmission;
    transmission.shiftToGear(3);
    transmission.upShift();
    EXPECT_EQ(transmission.getCurrentGear(), 4); // Fourth

    transmission.upShift();
    transmission.upShift();
    transmission.upShift(); // Should not go beyond Sixth
    EXPECT_EQ(transmission.getCurrentGear(), 6); 
}

TEST(TransmissionTests, DownshiftWorks) {
    Transmission transmission;
    transmission.shiftToGear(3);
    transmission.downShift();
    EXPECT_EQ(transmission.getCurrentGear(), 2); // Second
    transmission.downShift();
    EXPECT_EQ(transmission.getCurrentGear(), 1); // First
    transmission.downShift();
    EXPECT_EQ(transmission.getCurrentGear(), 1); // Should not go below First
}

TEST_P(GearRatioTests, GearRatiosAreCorrect) {
    int gear = GetParam().first;
    float expectedRatio = GetParam().second;

    Transmission transmission;
    transmission.shiftToGear(gear);
    EXPECT_FLOAT_EQ(transmission.getCurrentGearRatio(), expectedRatio);
}

INSTANTIATE_TEST_SUITE_P(
    TransmissionGearRatioTests,
    GearRatioTests,
    ::testing::Values(
        std::make_pair(0, 0.0f), // Neutral
        std::make_pair(1, 3.64f), // First
        std::make_pair(2, 2.08f), // Second
        std::make_pair(3, 1.36f), // Third
        std::make_pair(4, 1.02f), // Fourth
        std::make_pair(5, 0.83f), // Fifth
        std::make_pair(6, 0.66f)  // Sixth
    )
);
