import React, {useState, useEffect} from 'react';
import './DigitalClock.css';

function DigitalClock({x, y}) {
    const [time, setTime] = useState(new Date());

    useEffect(() => {
        const timer = setInterval(() => {
            setTime(new Date());
        }, 1000);

        return () => clearInterval(timer);
    }, []);

    const formatTime = (date) => {
        const hours = date.getHours() % 12 || 12; // Convert to 12-hour format
        const minutes = date.getMinutes().toString().padStart(2, '0');

        return hours < 10 ? `0${hours}:${minutes}` : `${hours}:${minutes}`;
    };

    return (
        <text x={x} y={y} className="digital-clock">
            {formatTime(time)}
        </text>
    );
}

export default DigitalClock;