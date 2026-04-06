#include "Transmission.h"
#include <iostream>

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