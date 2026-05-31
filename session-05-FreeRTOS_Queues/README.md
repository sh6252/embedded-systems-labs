# FreeRTOS Queues 🌈

A cute project that shows how to use a Queue in FreeRTOS on ESP32.

What happens here:
- A button press is detected in one task
- The press value is sent to a queue
- Another task receives the value and turns an LED on/off

Recommended hardware:
- ESP32
- Button connected to `GPIO4`
- On-board or external LED on `GPIO2`

How to use:
1. Open the project in PlatformIO.
2. Upload it to the ESP32.
3. Open the serial monitor and watch "Sent" and "Received" messages.

Why it is cute:
- It shows a simple button and LED interaction.
- It uses a Queue to pass data between tasks.
- It includes a basic debounce example so the button does not double-trigger.

Let your ESP32 talk to itself in an orderly way! 🐣
