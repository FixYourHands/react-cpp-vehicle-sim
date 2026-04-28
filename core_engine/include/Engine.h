#pragma once
#include "Transmission.h"
#include "FuelTank.h"

class Engine
{
private:
	float m_currentRPM;
	float m_maxTorque;
	float m_outputTorque;
public:
	Engine(float maxTorque = 400.f);
	void update(float throttleInput, float deltaTime, FuelTank& fuelTank, Transmission& transmission);
	float getOutputTorque() const;
	float getRPM() const;

};