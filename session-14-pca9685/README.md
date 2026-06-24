# Session 14 - PCA9685 Servo Control

Raspberry Pi servo control using the PCA9685 16-channel PWM driver over I2C.

This session demonstrates servo calibration and angle control from terminal input.

---

## Projects

- `servo_sweep.py` - Basic servo sweep between 0°, 90° and 180°
- `angle_input.py` - Control one servo by entering an angle from the terminal

---

## Features

- Raspberry Pi I2C communication
- PCA9685 16-channel PWM controller
- Servo calibration
- Terminal-based angle control
- Smooth servo movement

---

## Hardware Used

- Raspberry Pi 3 Model B
- PCA9685 PWM Driver
- MG996R Servo Motor
- External 5V Power Supply

---

## Calibration

```
Servo model: MG996R
Pulse width range: 500–2500 µs
Channels used: 0, 1
Actual range achieved: 0–180 degrees
```
---

## Technologies Used

- Raspberry Pi
- Python
- I2C
- PCA9685
- PWM
- Adafruit ServoKit


---

## Notes

The original assignment required controlling three servos.

This implementation demonstrates the same concepts using two MG996R servos because only two servos were available.


