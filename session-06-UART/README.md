# UART Examples

This folder contains two UART-based examples for ESP32.

## UART_Task1
- A simple serial command interface.
- Send `1` over the serial monitor to turn the onboard LED on.
- Send `0` over the serial monitor to turn the onboard LED off.
- Useful for learning basic Serial input handling.

## UART_Task2
- A UART loopback test using `Serial` and `Serial2`.
- Whatever you type into the main serial monitor is forwarded to `Serial2`.
- The board reads back the message from `Serial2` and prints it again.
- Great for exploring hardware serial communication and debugging UART wiring.

## How to use
1. Open the project in PlatformIO.
2. Select the example folder you want to run.
3. Upload the code to your ESP32.
4. Open the serial monitor at `115200` baud.

## Notes
- `UART_Task1` uses the default `Serial` port for commands.
- `UART_Task2` uses `Serial2` on pins `TX2_PIN = 17` and `RX2_PIN = 16`.
- Both examples are designed for quick experimentation with serial communication.
