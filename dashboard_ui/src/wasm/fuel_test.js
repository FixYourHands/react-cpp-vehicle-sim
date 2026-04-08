import initModule from './fuel_tank.js';

const Module = await initModule();

const fuelTank = new Module.FuelTank(1000);
console.log(`Initial fuel level: ${fuelTank.getCurrentLevel()} milliliters`);
fuelTank.consume(250);
console.log(`Fuel level after consumption: ${fuelTank.getCurrentLevel()} milliliters`);
fuelTank.refuel(500);
console.log(`Fuel level after refilling: ${fuelTank.getCurrentLevel()} milliliters`);