import React, { useState, useRef, useEffect } from 'react';

export function calculateMileRange(Module) {
    const [mileRange, setMileRange] = useState(0);
    const vehicleRef = useRef(null);
    const milesPerGallon = Math.random() * (31-26) + 26; // Simulate miles per gallon between 26 and 31
    const fuelTankCapacity = 11.0; // in gallons

    useEffect(() => {
        if (Module) {
            vehicleRef.current = new Module.Car();
            syncState();
        }
    }, [Module]);

    const syncState = () => {
        const telemetryData = vehicleRef.current.getTelemetryData();
        const range = telemetryData.fuelRemainingPercentage / 100 * milesPerGallon * fuelTankCapacity;
        setMileRange(range);
    }

    const updateMileRange = () => {
        if (!vehicleRef.current)
            return;

        syncState();
    }

    return {
        milesPerGallon,
        mileRange,
        updateMileRange
    };
}