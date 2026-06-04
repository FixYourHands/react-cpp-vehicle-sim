import React, {useState, useEffect} from 'react';
import './WeatherDisplay.css';

function WeatherDisplay({x, y, city="Phoenix"}) {
    const [temperature, setTemperature] = useState(null);
    const [error, setError] = useState(false);

    const API_KEY = "e87d0f763efc92cef50d6aae0a540cd7";

    useEffect(() => {
        const fetchWeather = async () => {
            try {
                const response = await fetch(`https://api.openweathermap.org/data/2.5/weather?q=${city}&units=imperial&appid=${API_KEY}`);
                if (!response.ok) {
                    throw new Error("Network response was not ok");
                }
                const data = await response.json();
                setTemperature(Math.round(data.main.temp));
            } catch (err) {
                console.error("Failed to fetch weather data:", err);
                setError(true);
            }
        };

        fetchWeather();
        const intervalId = setInterval(fetchWeather, 30 * 60 * 1000); // Refresh every 30 minutes

        return () => clearInterval(intervalId);
    }, [city]);

    const displayTemp = error || temperature === null ? "72" : `${temperature}`;

    return (
        <text x={x} y={y} className="weather-display">
            {displayTemp}°F
        </text>
    );
}

export default WeatherDisplay;