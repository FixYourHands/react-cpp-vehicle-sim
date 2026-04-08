#include "FuelTank.h"
#include <emscripten/bind.h>

FuelTank::FuelTank(int capacity)
	: m_capacity(capacity), m_currentLevel(capacity/2), m_lowFuelThreshold(capacity / 10), m_isLow(false) {
}

void FuelTank::checkLowFuel() {
	m_isLow = (m_currentLevel <= m_lowFuelThreshold);
}

void FuelTank::refuel(int amount) {
	m_currentLevel += amount;
	if (m_currentLevel > m_capacity) {
		m_currentLevel = m_capacity; // Prevent overfilling
	}
	checkLowFuel();
}

void FuelTank::consume(int amount) {
	m_currentLevel -= amount;
	if (m_currentLevel < 0) {
		m_currentLevel = 0; // Prevent negative fuel level
	}
	checkLowFuel();
}

int FuelTank::getCurrentLevel() const {
	return m_currentLevel;
}

int FuelTank::getCapacity() const {
	return m_capacity;
}

float FuelTank::getCurrentPercentage() const {
	return (static_cast<float>(m_currentLevel) / m_capacity) * 100.0f;
}

bool FuelTank::isEmpty() const {
	return m_currentLevel == 0;
}

bool FuelTank::isLow() const {
	return m_isLow;
}
