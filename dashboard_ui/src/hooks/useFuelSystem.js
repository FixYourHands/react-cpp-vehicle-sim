import React, {useState, useRef, useEffect} from 'react';

export function useFuelSystem(Module, capacity) {
    const [level, setFuel] = useState(0);
    const [fuelPercentage, setFuelPercentage] = useState(0);
    const [isLowFuel, setIsFuelLow] = useState(false);

    const [telemetryData, setTelemetryData] = useState({
        currentFuelLevel: 0,
        fuelRemainingPercentage: 0,
        isFuelLow: false
    });
    const vehicleRef = useRef(null);


    useEffect(() => {
        if (Module){
            vehicleRef.current = new Module.Car();
            syncState();
        }
    },[Module,capacity]);

    const syncState = () =>{
        const telemetryData = vehicleRef.current.getTelemetryData();     
        setTelemetryData({
            currentFuelLevel: telemetryData.currentFuelLevel,
            fuelRemainingPercentage: telemetryData.fuelRemainingPercentage,
            isFuelLow: telemetryData.isFuelLow
        });
    }

    const updateFuel= (newValue) => {
        if (!vehicleRef.current)
            return;
        const currentLevel = telemetryData.currentFuelLevel;
        const diff = newValue - currentLevel;

        if (diff > 0){
            vehicleRef.current.refuel(diff);
        }
        else if (diff < 0){
            vehicleRef.current.consumeFuel(Math.abs(diff));
        }

        syncState();
    }

    return {
        // level: telemetryData.currentFuelLevel,
        // fuelPercentage: telemetryData.fuelRemainingPercentage,
        // isLowFuel: telemetryData.isFuelLow,
        telemetryData,
        updateFuel
    };

}