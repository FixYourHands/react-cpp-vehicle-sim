#pragma once

namespace WheelConstants {
    inline constexpr float CIVIC_TIRE_DIAMETER_INCHES {25.0f};
    inline constexpr float CIVIC_TIRE_WIDTH_INCHES {10.5f};
    inline constexpr float CIVIC_TIRE_MASS_KG {15.0f};
    inline constexpr float VELOCITY_DAMPING_FACTOR {0.99f}; // Damping factor to prevent infinite acceleration
}

namespace PhysicsConstants {
    inline constexpr float GRAVITY {9.81f}; // m/s^2
    inline constexpr float DRIVETRAIN_EFFICIENCY {0.85f};
    inline constexpr float FRONT_WEIGHT_DISTRIBUTION {0.6f}; // 60% weight on front wheels
    inline constexpr float FRICTION_COEFFICIENT {0.9f}; // Typical tire-road friction coefficient
    inline constexpr float METERS_PER_SECOND_TO_MPH {2.23694f}; // 1 m/s = 2.23694 mph
    inline constexpr float INCH_TO_METER {0.0254f};
    inline constexpr float ANGULAR_VELOCITY_TO_RPM {9.5493f}; // 1 rad/s = 9.5493 RPM

}

namespace TachometerConstants {
    inline constexpr float MAX_RPM {8000.0f};
    inline constexpr float SMOOTHING_FACTOR {1.0f}; // Higher value means faster response
}

namespace FuelConstants {
    inline constexpr float MAX_FUEL_CAPACITY {1000.0f}; // in arbitrary fuel units
    inline constexpr float FUEL_CONSUMPTION_RATE {10.0f}; // fuel units consumed per second at full throttle
    inline constexpr float LOW_FUEL_PERCENTAGE {10.0f}; // 10% of capacity
}

namespace EngineConstants {
    inline constexpr float MAX_TORQUE {400.0f}; // in Nm
    inline constexpr float IDLE_RPM {800.0f};
    inline constexpr float MAX_RPM {8000.0f};
    inline constexpr float RPM_INCREASE_RATE {5000.0f}; // RPM increase per second at full throttle
    inline constexpr float RPM_DECREASE_RATE {1000.0f}; // RPM decrease per second when not throttling
    inline constexpr float ENGINE_FRICTION_DECAY_RATE {500.0f}; // RPM decrease per second due to engine friction when not throttling
    inline constexpr float TORQUE_CURVE_LOW_THRESHOLD {2500.0f}; // RPM below which torque starts to drop
    inline constexpr float TORQUE_CURVE_HIGH_THRESHOLD {4500.0f}; // RPM above which torque starts to drop
    inline constexpr float TORQUE_CURVE_FALLOFF_RATE {3500.0f}; // Rate at which torque falls off outside the optimal RPM range

}

namespace TransmissionConstants {
    inline constexpr float FINAL_DRIVE_RATIO {3.842f};
    inline constexpr std::array<float, 7> GEAR_RATIOS{0.0f, 3.64f, 2.08f, 1.36f, 1.02f, 0.83f, 0.66f}; // Neutral + 6 gears
}

namespace CarConstants {
    inline constexpr float MASS_IN_KG {1360.0f}; // Average mass of a compact car
}