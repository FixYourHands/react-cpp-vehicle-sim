function FuelGauge({size,fuelLevel,capacity,isLow}){
    const totalLength = 65
    const offset = totalLength - (fuelLevel/capacity) * totalLength;

    return (
    <svg width={size} height={size} viewBox = "0 0 100 100">
        <defs>
            <filter id="glow"
                x="-50%"
                y="-50%"
                width="200%"
                height="200%"
            >
                <feGaussianBlur stdDeviation="1.5" result="coloredBlur"/>
                <feMerge>
                    <feMergeNode in="coloredBlur"/>
                    <feMergeNode in="SourceGraphic"/>
                </feMerge>
            </filter>
        </defs>

        {/*background*/}
        <g transform="translate(100 0) scale (-1 1) rotate(-90 50 50)">
        <path 
            d="M 20 80 A 40 30 0 0 1 80 80" fill="none" stroke="#222" 
            strokeWidth={8}
            strokeLinecap="round"
            />

        {/*active fuel level*/}
        <path 
            d ="M 20 80 A 40 30 0 0 1 80 80" fill="none" stroke={isLow ? "#ff4d4d" : "#00d4ff"}
            strokeWidth={7}
            strokeDasharray={totalLength}
            strokeDashoffset={offset}
            strokeLinecap="round"
            filter="url(#glow)"
            style={{transition: 'stroke-dashoffset 0.5s ease-out, stroke 0.3s'}}
        />

        {/*segment mask */}
        <path
            d="M 20 80 A 40 30 0 0 1 80 80" fill="none" stroke="#111"
            strokeWidth={7}
            strokeDasharray="1, 4"
        />
        </g>
    </svg>
    );
}

export default FuelGauge;