import React, {useState, useRef, useEffect} from 'react';

export function useFuelSystem(Module, capacity) {
    const [level, setFuel] = useState(75);
    const [fuelPercentage, setFuelPercentage] = useState(0)
    const [isLowFuel, setIsFuelLow] = useState(false)
    const fuelTankRef = useRef(null)
    

    useEffect(() => {
        if (Module){
            fuelTankRef.current = new Module.FuelTank(capacity);
            syncState();
        }
    },[Module,capacity]);

    const syncState = () =>{
        setFuel(fuelTankRef.current.getCurrentLevel());
        setFuelPercentage(fuelTankRef.current.getCurrentPercentage());
        setIsFuelLow(fuelTankRef.current.isLow());
    }

    const updateFuel= (newValue) => {
        if (!fuelTankRef.current)
            return;
      const currentLevel = fuelTankRef.current.getCurrentLevel();
      const diff = newValue - level;

      if (diff > 0){
        fuelTankRef.current.refuel(diff);
      }
      else if (diff < 0){
        fuelTankRef.current.consume(Math.abs(diff));
      }

      syncState();
    }

    return {level, fuelPercentage, isLowFuel, updateFuel}
}