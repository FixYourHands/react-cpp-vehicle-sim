import FuelGaugeDisplay from "./FuelGaugeDisplay";
import { useFuelSystem } from "../../hooks/useFuelSystem.js";


function FuelSystem({fuelTelemetryData, updateFuel}) {
    const capacity = 41639.5;
    const fuelGaugeSize = 250;
    const {currentFuelLevel: level, fuelRemainingPercentage: fuelPercentage, isFuelLow: isLowFuel} = fuelTelemetryData;

    console.log(level)
    return (
      <div className="dashboard-container">
        <FuelGaugeDisplay size={fuelGaugeSize} fuelLevel={level} capacity={capacity} isLow={isLowFuel}/>
        <div className="controls">
          <p>Fuel Level: {Math.round(fuelPercentage)}%</p>
          <input
            type="range"
            min="0"
            max={capacity}
            value={level}
            onChange={(e) => updateFuel(Number(e.target.value))}
            className="slider"
            />
        </div>
      </div>
    );
}

export default FuelSystem;