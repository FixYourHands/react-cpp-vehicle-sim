import {Card} from 'react-bootstrap';
import ReactSpeedometer from 'react-d3-speedometer';

const speed = 20;

const Speedometer = ({speed}) => {
    return (
        <div className="relative w-[800px] h-[400px] bg-black flex items-center justify-center">
            <ReactSpeedometer
                    //value={speed}
                    minValue={0}
                    maxValue={8}
                    width={700}
                    height={400}
                    segments={9}
                    needleColor="#df3e0d"
                    startColor="#c42d07"
                    endColor="#c42d07"
            />

            <div className="absolute flex flex-col items-center justify-center translate-y-4">
                <h1 className="text-8xl font bold text-white tracking tighter">
                    {speed}
                </h1>
                <span className="text-xl font-medium text-white uppercase">
                    mph
                </span>
            </div>

        </div>
        
    );
}

export default Speedometer;