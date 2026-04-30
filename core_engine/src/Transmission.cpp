#include "Transmission.h"
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

Transmission::Transmission()
	: m_currentGear(Gear::Neutral) {
}

int Transmission::getCurrentGear() const {
	return static_cast<int>(m_currentGear);
}

float Transmission::getCurrentGearRatio() const {
	return m_gearRatios[static_cast<int>(m_currentGear)];
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
	if (m_currentGear != Gear::First) {
		m_currentGear = static_cast<Gear>(static_cast<int>(m_currentGear) - 1);
	}
	else {
		std::cout << "Already in first gear!" << std::endl;
	}
}

void Transmission::neutralShift() {
	m_currentGear = Gear::Neutral;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(transmission_module) {
	emscripten::class_<Transmission>("Transmission")
		.constructor<>()
		.function("getCurrentGear", &Transmission::getCurrentGear)
		.function("getCurrentGearRatio", &Transmission::getCurrentGearRatio)
		.function("upShift", &Transmission::upShift)
		.function("downShift", &Transmission::downShift)
		.function("neutralShift", &Transmission::neutralShift);
}
#endif