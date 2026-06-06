import "./Speedometer.css";

function SpeedometerDisplay({ x, y, speed }) {

  return (
    <g className=".digital-speedometer">
      <text
        x={x}
        y={y}
        textAnchor="middle"
        fontSize="48"
        fill="white"
        className="speed-value"
      >
        {speed}
      </text>
      
    </g>
  );
}

export default SpeedometerDisplay;
