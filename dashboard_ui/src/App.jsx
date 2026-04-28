import './App.css';

import FuelSystem from "./components/FuelSystem/FuelSystem.jsx"
import TachometerDisplay from './components/Tachometer/TachometerDisplay.jsx';

function App({Module}) {
    return (
      <div className="dashboard-container">
        {/*<FuelSystem Module={Module} /> */}
        <TachometerDisplay />
      </div>
    );
}

export default App;

