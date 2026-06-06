import './MileRange.css';
import {calculateMileRange} from '../../hooks/calculateMileRange';

function MileRange({Module, x, y}) {
    const {milesPerGallon, mileRange, updateMileRange} = calculateMileRange(Module);

    return (
        <g className="range">
            <text x={x} y={y} className="range-label">
                <tspan className="range-label">Range: </tspan>
                <tspan dx="50" className="range-value"> {Math.round(mileRange)} </tspan>
                <tspan dx="-3" dy="1" className="range-unit"> miles</tspan>
            </text>

            <text x={x} y={y+30} className="range-label">
                <tspan>Average Fuel A</tspan>
                <tspan dx="10" className="range-value">{milesPerGallon.toFixed(1)}</tspan>
                <tspan dx="2" dy="2" className="range-unit"> mpg</tspan>
            </text>
        </g>
    );
}

export default MileRange;