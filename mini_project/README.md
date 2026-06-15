# Smart Plant Monitor

## Mini Project

A smart plant monitor that reads temperature and humidity from a DHT22 sensor, simulates soil moisture with a potentiometer, sends data to Arduino Cloud, exposes sensor data through BLE, and displays live values on an Arduino Cloud dashboard.

- Student: Shifra
- Mentor: Dosithee Miet
- Date: 15/06/2026

## Hardware Components

- ESP32 DevKit
- DHT22 temperature and humidity sensor
- 10k potentiometer (soil moisture simulation)
- Green LED (WiFi indicator)
- Red LED (alert indicator)
- 150 Ω resistors ×2
- 10k pull-up resistor for DHT22 data line
- Breadboard and jumper wires

## How to Run in Wokwi

1. Open `mini_project/wokwi/diagram.json` in Wokwi.
2. Open the sketch `mini_project/final-code/PlantMonitor_jun10a.ino`.
3. Verify the board is ESP32 DevKit and the DHT22 and potentiometer are wired as shown.
4. Start the simulation.
5. Open the Serial Monitor to observe task execution, sensor readings, and system status messages.

## How to Connect to Arduino Cloud

1. Create an Arduino Cloud account at https://app.arduino.cc.
2. Create a Thing named `PlantMonitor`.
3. Add the required Cloud variables:
   - `temperature` (float)
   - `humidity` (float)
   - `moisture` (int)
   - `wifiStatus` (bool)
   - `alertActive` (bool)
4. Download the generated `thingProperties.h` file and place it in the project folder.
5. Configure the credentials in `arduino_secrets.h`.
6. Upload the project to the ESP32 and verify that the dashboard receives live updates.

## What Each FreeRTOS Task Does

- `sensorTask` — reads DHT22 temperature and humidity and reads the potentiometer ADC for soil moisture every 2 seconds.
- `cloudTask` — updates Arduino Cloud variables from the shared globals every 5 seconds.
- `bleTask` — updates the BLE characteristic with the latest sensor data every 2 seconds and notifies connected BLE clients.
- `alertTask` — checks thresholds every 500 ms and controls the green/red LEDs and alert flags.
- `displayTask` — prints a formatted status table to the Serial Monitor every second.

## Wiring Summary

- DHT22 VCC → ESP32 3.3V
- DHT22 DATA → ESP32 GPIO4 with 10k pull-up resistor to 3.3V
- DHT22 GND → ESP32 GND
- Potentiometer left pin → 3.3V
- Potentiometer right pin → GND
- Potentiometer wiper → ESP32 GPIO3
- Green LED anode → GPIO2 via 150 Ω resistor, cathode → GND
- Red LED anode → GPIO5 via 150 Ω resistor, cathode → GND

## Dashboard Screenshot / Link

- Screenshot file: `mini_project/Dashboard.png`
- Live Arduino Cloud dashboard link: `[Plant Monitor Dashboard](https://app.arduino.cc/dashboards/afeb53c8-fe97-4621-8fa7-a72edb72a43e?page=6b95caa4-43bf-48a1-bd1e-b6a32febe0ab&mode=view)`

## Notes

- The alert system sets `alertActive = true` for temperature above 30°C or soil moisture below 20%.
- The green LED indicates WiFi/cloud connection status.
- The red LED warns when the plant needs water or when temperature is too high.
