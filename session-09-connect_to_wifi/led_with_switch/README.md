# led_with_switch

A small and friendly project that controls an LED with a switch, while connecting to WiFi and printing status to Serial.

## What the code does

- reads the switch state
- turns an LED on and off
- connects to WiFi and prints status messages to Serial

## Important files

- `Untitled_jun08b.ino` - main Arduino sketch
- `arduino_secrets.h` - WiFi network name and password
- `thingProperties.h` - project settings
- `sketch.json` - Arduino project configuration

## How to run

1. Open the `led_with_switch` folder in PlatformIO or Arduino IDE.
2. Update `arduino_secrets.h` with your WiFi credentials.
3. Connect the ESP32, switch, and LED according to the circuit.
4. Upload the code to the ESP32.
5. Open the Serial Monitor and see the switch and LED status.

## What you can improve

- send the LED status to a server or cloud service
- add another switch and control more LEDs
- use a simple web interface instead of Serial

Have fun! 💡
