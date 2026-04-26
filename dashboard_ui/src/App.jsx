import Speedometer from "./components/Speedometer";
import FuelGauge from "./components/FuelGauge";
import './App.css';

import { useFuelSystem } from "./hooks/useFuelSystem.js";


function App({Module}) {
    const capacity = 1000;
    const fuelGaugeSize = 250;
    const {level, fuelPercentage, isLowFuel, updateFuel} = useFuelSystem(Module,capacity);

    console.log(fuelPercentage)
    return (
      <div className="dashboard-container">
        <FuelGauge size={fuelGaugeSize} fuelLevel={level} capacity={capacity} isLow={isLowFuel}/>
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

export default App;

