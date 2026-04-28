import "./Tachometer.css";

function TachometerDisplay({ rpm }) {

    const radius = 212;
    const circumference = Math.PI * radius;
    const dashOffset = circumference - (100/8050) * circumference;
  return (
    <svg width="550" height="450" viewBox="0 0 500 400">
      <defs>
        <linearGradient id="arcFade" x1="0%" y1="0%" x2="0%" y2="100%">
          <stop
            offset="0%"
            style={{ stopColor: "#D85B52", stopOpacity: 0.8 }}
          />

          <stop offset="15%" style={{ stopColor: "#C04F4E", stopOpacity: 1 }} />

          <stop offset="90%" style={{ stopColor: "#7B3231", stopOpacity: 1 }} />
        </linearGradient>
      </defs>

      {/*outer white ring */}
      <path d="M 10 300 A 220 220 0 0 1 450 300" className="outer-ring-white" />

      {/*outer bright red ring */}
      <path
        d="M 18 300 A 212 212 0 0 1 442 300"
        className="outer-ring-red"
        style={{ stroke: "url(#arcFade)", fill: "none" }}
      />

      {/*middle dark ring */}
      <path d="M 25 300 A 205 205 0 0 1 435 300" className="middle-ring-red" />

      {/*inner red ring */}
      <path d="M 30 300 A 200 200 0 0 1 430 300" className="inner-ring-red" />

      {/*outer dark ring */}
      <path
        d="M 55 300 A 175 175 0 0 1 405 300"
        className="outer-ring-dark-red"
      />

      {/*NUMBERS CODE */}
      <g className="rpm-numbers">
        {[...Array(33)].map((_, i) => {
          const angleInDegrees = 180 - i * (180 / 32);
          const angleInRadians = (angleInDegrees * Math.PI) / 180;

          const centerX = 230;
          const centerY = 295;

          // Define different lengths for the tics
          let tickLength = 5; // Default Small Tic
          let strokeWidth = 1;

          if (i % 4 === 0) {
            tickLength = 15; // Major Tic
            strokeWidth = 2.5;
          } else if (i % 2 === 0) {
            tickLength = 10; // Half Tic
            strokeWidth = 1.5;
          }

          // Radius logic: Start them just outside the dark bar (radius 175)
          const innerR = 195;
          const outerR = innerR + tickLength;

          const x1 = centerX + innerR * Math.cos(angleInRadians);
          const y1 = centerY - innerR * Math.sin(angleInRadians);
          const x2 = centerX + outerR * Math.cos(angleInRadians);
          const y2 = centerY - outerR * Math.sin(angleInRadians);

          return (
            <g key={i}>
              <line
                key={i}
                x1={x1}
                y1={y1}
                x2={x2}
                y2={y2}
                stroke="white"
                strokeWidth={strokeWidth}
                strokeLinecap="butt"
              />
              {i % 4 === 0 && (
                <text
                  x={centerX + 180 * Math.cos(angleInRadians)}
                  y={centerY - 175 * Math.sin(angleInRadians)}
                  className="rpm-number"
                >
                  {i / 4}
                </text>
              )}
            </g>
          );
        })}
      </g>
      {/* The MOVING RPM BAR */}
      <path
        d="M 15 300 A 210 210 0 0 1 445 300"
        fill="none"
        opacity={1}
        stroke="red"
        strokeWidth="12"
        strokeDasharray={circumference}
        strokeDashoffset={dashOffset}
        style={{ transition: "stroke-dashoffset 0.1s ease-out" }}
      />
    </svg>
  );
}

export default TachometerDisplay;
