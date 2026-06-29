# Embedded Systems Labs 🔧

A collection of embedded systems projects focusing on firmware, hardware interfacing, and applied microcontroller development.

Each folder contains an individual lab that demonstrates a specific embedded systems concept, including I/O control, sensor integration, communication protocols, and real-world robotics applications.

- `Traffic lights`: traffic signal sequencing using FreeRTOS and task scheduling.
- `RGB, Brightness LED & Servo`: RGB LED control, brightness adjustment, and servo motion with a keypad interface.
- `Smart Robot Status Monitor`: environmental and distance monitoring for a compact robot platform.
- `FreeRTOS Queues`: inter-task communication with queues and button-controlled LED signaling.
- `UART communication`: serial and UART examples for talking to the board and loopback testing
- `DHT22 sensor`: temperature and humidity sensing with warning indicators.
- `connect_to_wifi-arduino_IoT_cloud`: Arduino IoT Cloud integration for remote telemetry and device control.
- `BLE`: Bluetooth Low Energy communication on ESP32.
- `wifi_http`: WiFi HTTP client examples for weather API requests and remote reporting.
- `raspberryPI-gpio`: Raspberry Pi GPIO example for LED blink control using `gpiozero`.
- `pca9685`: PCA9685 servo control examples with Adafruit ServoKit.
- `hexLeg`: single-leg hexapod control using Raspberry Pi, PCA9685, and servo pose management.
- `UART Serial Bridge`: Raspberry Pi to ESP32 UART Serial Bridge examples for text and angle data exchange
- `angle-protocol`: JSON-based UART protocol between Raspberry Pi and ESP32 for remote hexapod servo control with FreeRTOS and PCA9685.

## Learning Outcomes

- Embedded hardware interfacing with GPIO, PWM, I2C, and UART.
- Firmware design patterns for sensor monitoring and actuator control.
- Real-time task coordination using FreeRTOS.
- Serial communication and protocol parsing.
- Modular project structure for rapid hardware experimentation.

## Repository Usage

1. Select the project folder corresponding to the lab you want to run.
2. Review the included source files and hardware requirements.
3. Deploy the code to the target board using PlatformIO, Arduino, or native Python as appropriate.
4. Use the serial monitor, terminal, or connected hardware to observe and verify behavior.

## About This Repository

This repository is intended for hands-on embedded systems learning and prototyping. It is organized by session and emphasizes repeatable lab exercises for common microcontroller interfaces and communication methods.
