import React, {useState, useRef, useEffect} from 'react';

export function useFuelSystem(Module) {
    const [fuelTelemetryData, setTelemetryData] = useState({
        currentFuelLevel: 0,
        fuelRemainingPercentage: 0,
        averageMilesPerGallon: 0,
        milesRemaining: 0,
        isFuelLow: false
    });
    const vehicleRef = useRef(null);


    useEffect(() => {
        if (Module){
            vehicleRef.current = new Module.Car();
            syncState();
        }
    },[Module]);

    const syncState = () =>{
        const telemetryData = vehicleRef.current.getTelemetryData();     
        setTelemetryData({
            currentFuelLevel: telemetryData.currentFuelLevel,
            fuelRemainingPercentage: telemetryData.fuelRemainingPercentage,
            isFuelLow: telemetryData.isFuelLow,
            averageMilesPerGallon: telemetryData.averageMilesPerGallon,
            milesRemaining: telemetryData.rangeInMiles
        });
    }

    const updateFuel= (newValue) => {
        if (!vehicleRef.current)
            return;
        const currentLevel = fuelTelemetryData.currentFuelLevel;
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
        fuelTelemetryData,
        updateFuel
    };

}