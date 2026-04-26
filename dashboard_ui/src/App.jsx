import Speedometer from "./components/Speedometer";
import FuelGauge from "./components/FuelGauge";
import './App.css';
import initModule from './wasm/fuel_tank.js'
import { useFuelSystem } from "./hooks/useFuelSystem.js";

const Module = await initModule();

function App() {
    const capacity = 1000;
    const fuelGaugeSize = 250;
    const {level,fuelPercentage, isLowFuel, updateSlider} = useFuelSystem(Module,capacity);
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
            onChange={updateSlider}
            className="slider"
            />
        </div>
      </div>
    );
}

export default App;

