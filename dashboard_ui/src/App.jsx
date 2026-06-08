import './App.css';

import FuelSystem from "./components/FuelSystem/FuelSystem.jsx"
import TachometerDisplay from './components/Tachometer/TachometerDisplay.jsx';
import { useFuelSystem } from './hooks/useFuelSystem.js';


function App({Module}) {
    const {fuelTelemetryData, updateFuel} = useFuelSystem(Module);
    return (
      <div className="dashboard-container">
        <FuelSystem fuelTelemetryData={fuelTelemetryData} updateFuel={updateFuel} /> 
        <TachometerDisplay fuelTelemetryData={fuelTelemetryData} />
      </div>
    );
}

export default App;

