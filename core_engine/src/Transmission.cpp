#include "Transmission.h"
#include <iostream>
#include <emscripten/bind.h>

Transmission::Transmission()
	: m_currentGear(Gear::Neutral) {
}

int Transmission::getCurrentGear() const {
	return static_cast<int>(m_currentGear);
}

float Transmission::getCurrentGearRatio() const {
	return m_gearRatios[static_cast<int>(m_currentGear)];
}

void Transmission::upshift() {
	if (m_currentGear != Gear::Sixth) {
		m_currentGear = static_cast<Gear>(static_cast<int>(m_currentGear) + 1);
	}
	else {
		std::cout << "Already in highest gear!" << std::endl;
	}
}

void Transmission::downshift() {
	if (m_currentGear != Gear::Neutral) {
		m_currentGear = static_cast<Gear>(static_cast<int>(m_currentGear) - 1);
	}
	else {
		std::cout << "Already in neutral gear!" << std::endl;
	}
}

EMSCRIPTEN_BINDINGS(transmission_module) {
	emscripten::class_<Transmission>("Transmission")
		.constructor<>()
		.function("getCurrentGear", &Transmission::getCurrentGear)
		.function("getCurrentGearRatio", &Transmission::getCurrentGearRatio)
		.function("upshift", &Transmission::upshift)
		.function("downshift", &Transmission::downshift);
}