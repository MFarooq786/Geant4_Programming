# Fixed Target Detector Simulation with Geant4

This project simulates a detector for a fixed target experiment using [Geant4](https://geant4.web.cern.ch/). The setup includes a world volume, a sensitive detector, and a beam of particles directed at the detector. The simulation records detailed kinematic and dynamic properties of particles, storing the results in both CSV and ROOT formats for further analysis.

---

## **Project Structure**

### **1. Files Overview**
- **CMakeLists.txt**: Configuration file for building the Geant4 project using CMake.
- **sim.cc**: The main program file that initializes Geant4, sets up the geometry, physics, and actions, and starts the simulation with visualization.
- **construction.hh / construction.cc**: Defines the world and detector geometry.
- **physics.hh / physics.cc**: Configures the physics processes for the simulation (e.g., electromagnetic processes).
- **generator.hh / generator.cc**: Implements the particle gun to simulate an incident beam.
- **SensitiveDetector.hh / SensitiveDetector.cc**: Implements the sensitive detector that records particle interactions.
- **RunAction.hh / RunAction.cc**: Manages the run, initializing ROOT and CSV files, and storing event data.
- **EventAction.hh / EventAction.cc**: Handles the per-event actions and collects data from the sensitive detector.
- **action.hh / action.cc**: Initializes all user-defined actions.

---

## **2. Simulation Details**

### **Geometry**
- **World Volume**:
  - A cubic volume of \(1 \, \text{m}^3\) containing the detector.
  - Represents the simulation space.

- **Sensitive Detector**:
  - Records particle interactions, including position, momentum, energy, and other properties.

### **Particle Beam**
- **Particle Type**: Proton (\(p\)).
- **Energy**: 100 GeV.
- **Initial Position**: Origin \((0, 0, 0)\).
- **Momentum Direction**: Along the \(+Z\)-axis \((0, 0, 1)\).

### **Physics**
- Implements standard electromagnetic and optical physics processes for particles.
- Configures the interaction of particles with detector materials.

---

## **3. Kinematic and Dynamic Quantities**

The simulation records the following quantities for each particle step:

### **Kinematic Quantities**
- **ParticleType**: The type of particle (e.g., proton, electron).
- **MomentumMag**: Magnitude of the particle's momentum.
- **Theta (\( \theta \))**: Polar angle.
- **Phi (\( \phi \))**: Azimuthal angle.
- **Beta (\( \beta \))**: Velocity as a fraction of the speed of light.
- **Gamma (\( \gamma \))**: Lorentz factor.
- **TotalEnergy**: Total energy, including rest mass energy.

### **Dynamic Quantities**
- **Position (X, Y, Z)**: Particle position at each step.
- **EnergyDeposited (\( dE \))**: Energy lost by the particle.
- **StoppingPower (\( dE/dX \))**: Energy loss per unit length.
- **TrackLength (\( L \))**: Total distance traveled by the particle.
- **Time of Flight (TOF)**: Time taken for the particle to travel through the detector.

---

## **4. Output Files**
- **output.csv**:
  - Stores the recorded data in tabular format for easy analysis.
  - Columns: `EventID,ParticleType,MomentumMag,Theta,Phi,Beta,Gamma,TotalEnergy,PositionX,PositionY,PositionZ,EnergyDeposited,dEdx,TrackLength,TOF`.

- **output.root**:
  - ROOT file containing the same data in a structured tree format for advanced analysis using ROOT tools.

---

## **5. Building and Running**

### **Prerequisites**
- Geant4 installed and configured on your system.
- ROOT installed for handling ROOT files.

### **Build Instructions**
```bash
mkdir build
cd build
cmake ..
make

