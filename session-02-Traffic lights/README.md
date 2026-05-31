# Traffic Lights 🚦

A cute project that simulates traffic light operation with ESP32 and FreeRTOS.

What is included:
- car traffic light with red, yellow, and green LEDs
- pedestrian traffic light with red and green LEDs
- button to request pedestrian crossing
- task coordination using Mutex and FreeRTOS tasks

Recommended hardware:
- ESP32
- car LEDs on `GPIO32`, `GPIO33`, `GPIO25`
- pedestrian LEDs on `GPIO19`, `GPIO18`
- button on `GPIO17`

How to use:
1. Open the project in PlatformIO.
2. Upload it to the ESP32.
3. Press the button to request a pedestrian crossing.

Why it is cute:
- It creates a small traffic light scene with smooth behavior.
- The car and pedestrian lights are managed gracefully.
- The state transitions feel alive and orderly.

A charming little traffic light system, like a tiny city intersection. 🏙️
