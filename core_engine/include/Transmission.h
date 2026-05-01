#pragma once
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
	static constexpr std::array<float, m_maxGear + 1> m_gearRatios{
		0.0f, // Neutral
		3.64f, // First
		2.08f, // Second
		1.36f, // Third
		1.02f, // Fourth
		0.83f, // Fifth
		0.66f  // Sixth
	};
public:
	Transmission();
	int getCurrentGear() const;
	float getCurrentGearRatio() const;
	void upShift();
	void downShift();
	void shiftToGear(int gear);
	void neutralShift();
	bool isInNeutral() const;
	//bool canShift() const;
};