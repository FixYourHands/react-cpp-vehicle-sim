# WebAssembly Engine & Custom Telemetry Dashboard

A high-performance, real-time vehicle instrument cluster built using a **C++ simulation backend** compiled to **WebAssembly (WASM)**, seamlessly integrated with a responsive **React frontend**. 

The architecture enforces a strict separation of concerns: vehicle physics, fuel consumption dynamics, and rolling efficiency calculations run natively at 60 FPS in C++, while React operates purely as a stateless presentation layer utilizing high-performance SVG rendering.

## Project Showcases

### Main Instrument Cluster Layout
![Main Dashboard View](dashboard_ui/src/assets/cluster.png)
*Featuring a radial tachometer sweep (0-8000 RPM), central digital speedometer readout, localized environment widgets, and dynamic distance-to-empty tracking.*

### Diagnostic Controls & Fuel Telemetry
![Fuel Control System](dashboard_ui/src/assets/fuel.png)
*Real-time hardware emulation interface allowing granular tracking of raw fuel levels mapped directly to native C++ state variables.*

---

## Architectural Highlights


### 1. Embedded C++ Core Lifecycle (`Car.h`)
The heart of the simulation runs in native C++. Vehicle configuration metrics, mass constants, and volumetric capacities are centralized within `Constants.h`. 
* **Deterministic Fuel Volume Tracking:** The C++ core natively tracks fluid capacities down to the milliliter. Fuel levels are dynamically converted to precise tank percentages and mapped to fuel efficiency baselines.
* **Native Memory Management:** Exposes structured byte arrays directly to JavaScript via Emscripten bindings, maximizing performance by eliminating typical garbage collection overhead found in standard web apps.

### 2. State-Synchronized Telemetry Interfacing
The application relies on a single source of truth managed at the root and distributed down the tree via custom hooks:
* **`useFuelSystem`**: Acts as the dedicated bridge to the WebAssembly memory registers. It updates the underlying C++ class instances in response to user inputs and marshals the resulting telemetry buffers into reactive React state.
* **Unified Event Pipeline:** Interacting with the diagnostic UI slider immediately updates the core C++ volume counters, which triggers a top-down rendering frame pass across the dashboard display.

### 3. Stateless Presenter Components (`MileRange.jsx`)
The user interface components are fully decoupled from calculation logic. They receive pre-computed, structured props straight from the C++ telemetry payload:
* Zero calculation drift or structural desynchronization between different sections of the dashboard layout.
* Layout anchoring optimizes SVG text baselines natively, ensuring stable rendering during rapid telemetry updates.

---

## Technical Stack
* **Systems Core:** C++17, Emscripten (WASM Compiler)
* **Frontend UI:** React, Modern JavaScript (ES6+), SVG Data Articulation, HTML5 Canvas Elements
* **Styling Engine:** Custom CSS3 layout systems using dark-mode optimization palettes