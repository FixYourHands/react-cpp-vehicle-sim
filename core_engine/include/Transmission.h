#pragma once
#include "Constants.h"
#include <array>


enum class Gear
{
	Neutral,
	First,
	Second,
	Third,
	Fourth,
	Fifth,
	Sixth
};

class Transmission
{
	Gear m_currentGear;
	constexpr static int m_maxGear{ 6 };
	float m_FinalDriveRatio;
public:
	Transmission(float finalDriveRatio = TransmissionConstants::FINAL_DRIVE_RATIO);
	int getCurrentGear() const;
	float getCurrentGearRatio() const;
	float getFinalDriveRatio() const;
	float getTotalGearRatio() const;
	void upShift();
	void downShift();
	void shiftToGear(int gear);
	void neutralShift();
	bool isInNeutral() const;
	//bool canShift() const;
};