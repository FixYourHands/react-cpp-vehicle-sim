#include "Transmission.h"
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Transmission::Transmission(float finalDriveRatio)
	: m_currentGear(Gear::Neutral), m_FinalDriveRatio(finalDriveRatio) {
}

int Transmission::getCurrentGear() const {
	return static_cast<int>(m_currentGear);
}

float Transmission::getCurrentGearRatio() const {
	return TransmissionConstants::GEAR_RATIOS[static_cast<int>(m_currentGear)];
}

float Transmission::getFinalDriveRatio() const {
	return m_FinalDriveRatio;
}

float Transmission::getTotalGearRatio() const {
	return getCurrentGearRatio() * getFinalDriveRatio();
}

void Transmission::upShift() {
	if (m_currentGear != Gear::Sixth) {
		m_currentGear = static_cast<Gear>(static_cast<int>(m_currentGear) + 1);
	}
	else {
		std::cout << "Already in highest gear!" << std::endl;
	}
}

void Transmission::downShift() {
	if (m_currentGear != Gear::Neutral && m_currentGear != Gear::First) {
		m_currentGear = static_cast<Gear>(static_cast<int>(m_currentGear) - 1);
	}
	else {
		std::cout << "Already in first gear!" << std::endl;
	}
}

void Transmission::shiftToGear(int gear) {
	if (gear >= 0 && gear <= m_maxGear) {
		m_currentGear = static_cast<Gear>(gear);
	}
	else {
		std::cout << "Invalid gear: " << gear << std::endl;
	}
}

void Transmission::neutralShift() {
	m_currentGear = Gear::Neutral;
}

bool Transmission::isInNeutral() const {
	return m_currentGear == Gear::Neutral;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(transmission_module) {
	emscripten::class_<Transmission>("Transmission")
		.constructor<>()
		.function("getCurrentGear", &Transmission::getCurrentGear)
		.function("getCurrentGearRatio", &Transmission::getCurrentGearRatio)
		.function("getFinalDriveRatio", &Transmission::getFinalDriveRatio)
		.function("getTotalGearRatio", &Transmission::getTotalGearRatio)
		.function("upShift", &Transmission::upShift)
		.function("downShift", &Transmission::downShift)
		.function("neutralShift", &Transmission::neutralShift)
		.function("isInNeutral", &Transmission::isInNeutral)
		.function("shiftToGear", &Transmission::shiftToGear);
}
#endif