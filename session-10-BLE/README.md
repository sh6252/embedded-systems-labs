# BLE Example

A friendly Bluetooth Low Energy example for ESP32, showing how to connect and exchange data over BLE.

## What this project does

- sets up the ESP32 as a BLE device
- advertises a BLE service and characteristic
- allows a phone or another BLE client to connect and interact

## Important files

- `Untitled_jun08b.ino` - main Arduino sketch
- `arduino_secrets.h` - WiFi/credentials file (if used)
- `thingProperties.h` - project configuration
- `sketch.json` - project settings for Arduino

## How to run

1. Open the `session-10-BLE` folder in PlatformIO or Arduino IDE.
2. Upload the sketch to the ESP32.
3. Use a BLE app or device to scan for the ESP32.
4. Connect and explore the advertised service.

## Why this is cute

BLE is a great way to add wireless interaction without WiFi. This example is a good start for remote control, sensor data, or custom BLE-based projects.

Enjoy experimenting! 🔵
