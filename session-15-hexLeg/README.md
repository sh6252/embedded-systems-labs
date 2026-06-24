# 🤖 Session 15 – Hexapod Single Leg Control

## 📌 Overview
Control system for a single hexapod robot leg using:
- Raspberry Pi
- PCA9685 PWM driver
- 3 servos (HIP / FEMUR / TIBIA)

Features:
- Predefined poses
- Smooth motion control
- Step cycle simulation
- Keyboard control
- Custom experimental positions

---

## ⚙️ Hardware
- Raspberry Pi 3 / 4
- PCA9685 (I2C PWM driver)
- 3× Servo motors
- External 5V power supply

### Servo Mapping
- HIP → Channel 0
- FEMUR → Channel 1
- TIBIA → Channel 2

---

## 📐 Positions
### Base Positions
- HOME – neutral start position
- STAND – stable stance
- LIFT – leg lifted
- EXTEND – forward reach
- RETRACT – backward pull

### Custom Positions
- CROUCH – low bent stance `(90, 140, 40)`
- STRETCH – extended reach `(90, 70, 130)`
- BALANCE – stable mid pose `(100, 100, 80)`

---

## 🔁 Step Cycle
```
HOME → LIFT → EXTEND → STAND → RETRACT
```
- Runs in loops (e.g., 10 cycles)
- Measures execution time
- Calculates performance metrics (cycle time, steps/min)

---

## ⌨️ Keyboard Controls
- W → LIFT
- S → STAND
- A → RETRACT
- D → EXTEND
- H → HOME
- C → CROUCH
- T → STRETCH
- B → BALANCE
- Q / E → Rotate HIP

---

## 🚀 Run Instructions
```bash
python main.py
```

Choose mode in code:
- `step_cycle()` → automatic testing
- `keyboard_loop()` → manual control

---

## 🧠 Key Concepts
- Hardware abstraction via `HexLeg` class
- State-based motion system
- Smooth interpolation between poses
- Real-time control loop
- Modular robotics architecture
