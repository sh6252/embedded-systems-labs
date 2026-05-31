# DHT22 Project 🌤️

A simple and fun project for reading a DHT22 sensor on ESP32.

What is included:
- Reads temperature and humidity every 2 seconds
- Calculates a basic heat index
- Warning LED lights up when it is too hot or too humid
- A separate task blinks an LED

Recommended hardware:
- ESP32
- DHT22 sensor
- LED or indicator connected to `GPIO14`
- warning LED connected to `GPIO15`

How to use:
1. Open the project in PlatformIO.
2. Upload it to the ESP32.
3. Open the serial monitor and watch temperature and humidity readings.

Why it is cute:
- If it gets too hot or humid, there is a warning LED and "WARNING⚠️" in the console.
- There is also a nice blink mode showing the microcontroller is alive.

Enjoy! 😊
