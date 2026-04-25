function FuelGauge({size,fuelLevel}){
    const totalLength = 70
    const offset = totalLength - (fuelLevel/100) * totalLength;

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
        <path 
            d="M 20 80 A 40 40 0 0 1 80 80" fill="none" stroke="#222" 
            strokeWidth={8}
            strokeLinecap="round"
            />

        {/*active fuel level*/}
        <path 
            d ="M 20 80 A 40 40 0 0 1 80 80" fill="none" stroke={fuelLevel < 15 ? "#ff4d4d" : "#00d4ff"}
            strokeWidth={7}
            strokeDasharray={totalLength}
            strokeDashoffset={offset}
            strokeLinecap="round"
            filter="url(#glow)"
            style={{transition: 'stroke-dashoffset 0.5s ease-out, stroke 0.3s'}}
        />

        {/*segment mask */}
        <path
            d="M 20 80 A 40 40 0 0 1 80 80" fill="none" stroke="#111"
            strokeWidth={7}
            strokeDasharray="1, 4"
        />
        
    </svg>
    );
}

export default FuelGauge;