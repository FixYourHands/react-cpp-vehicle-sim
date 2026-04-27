import Speedometer from "./components/Speedometer";
import './App.css';

import FuelSystem from "./components/FuelSystem/FuelSystem.jsx"


function App({Module}) {
    return (
      <div className="dashboard-container">
        <FuelSystem Module={Module} />
      </div>
    );
}

export default App;

