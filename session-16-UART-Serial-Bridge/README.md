# Session 16 - UART Serial Bridge

Raspberry Pi to ESP32 UART communication examples for text and angle data transmission.

This session shows how to send serial data from a Raspberry Pi to an ESP32, receive it on the ESP32 UART port, and reply with a simple status response.

---

## Projects

- `starter-code/ESP32_uart_receiver.ino` - ESP32 UART receiver that echoes back acknowledgments.
- `starter-code/RPi_uart_sender.py` - Raspberry Pi sender that transmits "HELLO FROM RPI" and reads ESP32 replies.
- `send_angles/RPi_uart_sender.py` - Raspberry Pi sender that sends 18 random servo angles as comma-separated values.
- `send_angles/ESP32_uart_receiver.ino` - ESP32 UART receiver that parses angle values, prints each angle, and returns JSON status.

---

## Features

- Raspberry Pi UART serial transmission
- ESP32 UART reception
- Line-based message framing
- Comma-separated angle data parsing
- JSON status replies from ESP32
- KeyboardInterrupt-safe Python loop

---

## Hardware Used

- Raspberry Pi
- ESP32
- UART TX/RX connection
- Common ground
- Optional external 5V power supply

---

## Pin Connections

- Raspberry Pi `TX` → ESP32 `RXD2` (GPIO4)
- Raspberry Pi `RX` → ESP32 `TXD2` (GPIO5)
- Common ground between boards

---

## Run Instructions

1. Upload the appropriate ESP32 code to the ESP32.
2. Connect the Raspberry Pi UART pins to the ESP32 UART2 pins and share ground.
3. On the Raspberry Pi, run one of the sender scripts:
   - `python3 starter-code/RPi_uart_sender.py`
   - `python3 send_angles/RPi_uart_sender.py`

---

## Notes

- `starter-code` demonstrates basic text exchange and acknowledgment.
- `send_angles` demonstrates structured numeric data transfer for servo angles.
- The ESP32 replies with status information after receiving each line.
