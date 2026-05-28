#pragma once
#include "Transmission.h"
#include "FuelTank.h"
#include "Constants.h"

class Engine
{
private:
	float m_currentRPM;
	float m_maxTorque;
	float m_outputTorque;
	float m_throttleInput;
	float calculateTorqueMultiplier() const;
	bool m_isRunning;
public:
	Engine(float maxTorque = EngineConstants::MAX_TORQUE);
	void update(float deltaTime, FuelTank& fuelTank, Transmission& transmission);
	void setThrottleInput(float throttleInput);
	float getOutputTorque() const;
	float getRPM() const;
	void setRPM(float rpm);
	bool isRunning() const;
	void startEngine(const FuelTank& fuelTank);
	void stopEngine();

};