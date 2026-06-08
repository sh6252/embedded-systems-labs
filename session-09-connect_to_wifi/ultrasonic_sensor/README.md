# ultrasonic_sensor

A fun learning project for an ultrasonic distance sensor with ESP32 and WiFi connection.

## What the code does

- measures distance with an ultrasonic sensor
- prints the distance to Serial every few seconds
- connects to WiFi to show how a sensor can work with network access

## Important files

- `Untitled_jun08b.ino` - main Arduino sketch
- `arduino_secrets.h` - network credentials for WiFi
- `thingProperties.h` - project settings
- `sketch.json` - project configuration

## How to run

1. Open the `ultrasonic_sensor` folder in PlatformIO or Arduino IDE.
2. Update `arduino_secrets.h` with your WiFi SSID and password.
3. Connect the ultrasonic sensor and ESP32 according to the circuit.
4. Upload the code to the board.
5. Open the Serial Monitor and observe the distance readings.

## Pro tip

A few small code changes can turn this into a smart distance sensor that reports to the network.

Enjoy! 📏
