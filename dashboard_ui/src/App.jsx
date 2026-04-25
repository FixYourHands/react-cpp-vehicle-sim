import Speedometer from "./components/Speedometer";
import FuelGauge from "./components/FuelGauge";
import React, {useState} from 'react';
import './App.css';

function App() {
    const [level, setFuel] = useState(75);
    const [fuelGaugeSize, setFuelGaugeSize] = useState(350)
    const [speed, setSpeed] = useState(0)

    return (
      <div className="dashboard-container">
        <FuelGauge size={fuelGaugeSize} fuelLevel={level}/>
        <div className="controls">
          <p>Fuel Level: {level}%</p>
          <input
            type="range"
            min="0"
            max="100"
            value={level}
            onChange={(e) => setFuel(Number(e.target.value))}
            className="slider"
            />
        </div>
      </div>
    );
}

export default App;

