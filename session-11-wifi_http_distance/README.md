# WiFi & HTTP Communication 🌐📡

A dynamic duo of projects that connect your ESP32 to the internet and talk to remote servers!

What this project includes:

**wifi_http_get_weather.ino**
- Connects to WiFi and fetches live weather data via HTTP GET requests
- Parses JSON responses from the Open-Meteo weather API
- Displays current temperature and weather information over serial
- Perfect for building weather-aware IoT applications

**wifi_http_post_distance.ino**
- Combines ultrasonic distance sensing with HTTP POST requests
- Sends distance measurements to a remote server (httpbin.org)
- BLE communication for wireless interaction
- LED feedback when objects are detected within 5cm
- Multi-tasking with FreeRTOS for concurrent sensor reading and communication

Recommended hardware:
- ESP32
- Ultrasonic sensor (HC-SR04) on `TRIG_PIN 5`, `ECHO_PIN 27`
- Status LED on `GPIO4`
- WiFi network access (SSID and password required)

How to use:
1. Update WiFi credentials (SSID and password) in the code
2. Open the project in Arduino IDE or PlatformIO
3. Upload to your ESP32
4. For weather project: Open the serial monitor to see weather data updates
5. For distance project: Place objects near the sensor to trigger LED and server POST requests

Why it is cute:
- It brings the internet to your embedded system - how cool is that!
- Weather data makes your projects environment-aware and intelligent
- Distance sensing plus remote reporting creates a smart monitoring system
- The combination of HTTP GET and POST shows the full picture of web communication
- BLE + WiFi + Sensors working together gives you a truly connected device

Your ESP32 is now a little internet explorer! 🚀✨
