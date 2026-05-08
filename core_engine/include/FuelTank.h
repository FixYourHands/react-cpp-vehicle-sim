#pragma once

class FuelTank
{
private:
	float m_capacity; // in milliliters
	float m_currentLevel; // in milliliters
	float m_lowFuelThreshold; // in milliliters
	bool m_isLow; // Indicates if fuel is low
	void checkLowFuel();
public:
	FuelTank(float capacity = FuelConstants::MAX_FUEL_CAPACITY);
	float getCurrentPercentage() const;
	float getCurrentLevel() const;
	float getCapacity() const;
	void refuel(float amount);
	void consume(float amount);
	bool isEmpty() const;
	bool isLow() const;
};