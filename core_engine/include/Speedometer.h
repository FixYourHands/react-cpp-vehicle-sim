#pragma once

class Speedometer
{
	private:
		float m_tireDiameterInInches; // Diameter of the tire in inches
	public:
		Speedometer(float tireDiameterInInches);
		float calculateMPH(float wheelAngularVelocity) const;
};