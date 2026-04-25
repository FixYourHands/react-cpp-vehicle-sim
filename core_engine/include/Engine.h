#pragma once
#include "Transmission.h"
#include "FuelTank.h"

class Engine
{
	public:
	void update(float throttleInput, float deltaTime, FuelTank& fuelTank, Transmission& transmission);

};