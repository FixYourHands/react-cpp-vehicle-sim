import "./Speedometer.css";

function SpeedometerDisplay({ x, y, speed }) {

  return (
    <g classname=".digital-speedometer">
      <text
        x={x+30}
        y={y - 120}
        textAnchor="middle"
        fontSize="48"
        fill="white"
        className="speed-value"
      >
        {speed}
      </text>
      <text x={x+80} y={y - 120} textAnchor="middle" fontSize="24" fill="white" className="speed-unit">
        mph
      </text>
    </g>
  );
}

export default SpeedometerDisplay;
