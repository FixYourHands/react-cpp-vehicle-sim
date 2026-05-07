#pragma once
#include "Transmission.h"
#include "FuelTank.h"

class Engine
{
private:
	float m_currentRPM;
	float m_maxTorque;
	float m_outputTorque;
	float m_throttleInput;
	float calculateTorqueMultiplier() const;
public:
	Engine(float maxTorque = 400.f);
	void update(float deltaTime, FuelTank& fuelTank, Transmission& transmission);
	void setThrottleInput(float throttleInput);
	float getOutputTorque() const;
	float getRPM() const;
	void setRPM(float rpm);

};