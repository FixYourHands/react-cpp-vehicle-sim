#pragma once

class FuelTank
{
private:
	int m_capacity; // in milliliters
	int m_currentLevel; // in milliliters
	int m_lowFuelThreshold; // in milliliters
	bool m_isLow; // Indicates if fuel is low
	void checkLowFuel();
public:
	FuelTank(int capacity);
	float getCurrentPercentage() const;
	int getCurrentLevel() const;
	int getCapacity() const;
	void refuel(int amount);
	void consume(int amount);
	bool isEmpty() const;
	bool isLow() const;
};