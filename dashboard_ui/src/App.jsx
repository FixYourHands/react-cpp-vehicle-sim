import Speedometer from "./components/Speedometer";
import FuelGauge from "./components/FuelGauge";
import React, {useState, useRef, useEffect} from 'react';
import './App.css';
import initModule from './wasm/fuel_tank.js'

const Module = await initModule();

function App() {
    const [level, setFuel] = useState(75);
    const [fuelGaugeSize, setFuelGaugeSize] = useState(350)
    const [fuelPercentage, setFuelPercentage] = useState(0)
    const [lowFuel, setIsFuelLow] = useState(false)
    const capacity = 2000
    const fuelTankRef = useRef(null)
    

    useEffect(() => {
        fuelTankRef.current = new Module.FuelTank(capacity);
        setFuel(fuelTankRef.current.getCurrentLevel());
        setFuelPercentage(fuelTankRef.current.getCurrentPercentage());
        setIsFuelLow(fuelTankRef.current.isLow());
    },[]);

    const handleSliderChange = (e) => {
      const newValue = Number(e.target.value);
      const diff = newValue - level;

      if (diff > 0){
        fuelTankRef.current.refuel(diff);
      }
      else if (diff < 0){
        fuelTankRef.current.consume(Math.abs(diff));
      }

      setFuel(fuelTankRef.current.getCurrentLevel());
      setFuelPercentage(fuelTankRef.current.getCurrentPercentage());
      setIsFuelLow(fuelTankRef.current.isLow());

    }

    return (
      <div className="dashboard-container">
        <FuelGauge size={fuelGaugeSize} fuelLevel={level} capacity={capacity} isLow={lowFuel}/>
        <div className="controls">
          <p>Fuel Level: {Math.round(fuelPercentage)}%</p>
          <input
            type="range"
            min="0"
            max={capacity}
            value={level}
            onChange={handleSliderChange}
            className="slider"
            />
        </div>
      </div>
    );
}

export default App;

