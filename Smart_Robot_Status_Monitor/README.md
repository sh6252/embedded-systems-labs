# Smart Robot Status Monitor 🤖📡

A project that uses a DHT22 and ultrasonic sensor to monitor temperature, humidity, and distance.

What this project includes:
- temperature and humidity readings from the DHT22
- distance measurement in cm from an ultrasonic sensor
- a warning LED that lights when the distance falls below a threshold
- friendly serial output

Recommended hardware:
- ESP32
- DHT22 sensor on `GPIO21`
- TRIG on `GPIO4`
- ECHO on `GPIO16`
- status LED on `GPIO18`

How to use:
1. Open the project in PlatformIO.
2. Upload it to the ESP32.
3. Open the serial monitor to see temperature, humidity, and distance.

Why it is cute:
- The system not only reads sensors, it also shows a little alarm when something gets too close.
- Combining environment and proximity monitoring gives a smart robot vibe.

A great monitor for a small robot with personality. 💙
