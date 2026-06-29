# Session 17 - UART Protocol: Hexapod Servo Control

JSON-based UART communication protocol between Raspberry Pi and ESP32 for remote hexapod leg control.

This session demonstrates command-based servo control over serial communication with error validation.

---

## Features

- **JSON-based UART protocol** at 115200 baud
- **Command frame exchange**: Raspberry Pi sends 18 servo angles to ESP32
- **Acknowledgment and error responses** from ESP32
- **Servo control via PCA9685 PWM driver**
- **Hexapod leg kinematic abstraction** (HexLeg class)
- **Predefined leg positions** (HOME, STAND, LIFT, EXTEND, RETRACT, CROUCH, STRETCH, BALANCE)
- **FreeRTOS-based task architecture**
- **Input validation**: angle range (0-180°), joint count (18), JSON parsing

---

## Hardware Setup

### ESP32 Pins
- **UART2 RXD**: GPIO 4
- **UART2 TXD**: GPIO 5
- **I2C SDA**: GPIO 2
- **I2C SCL**: GPIO 3

### PCA9685 Configuration
- **I2C Address**: 0x40 (default)
- **PWM Frequency**: 50 Hz (standard servo)
- **Servo Channels**: 0–17 (18 servos)
- **Pulse Range**: 500–2500 µs

---

## Protocol Messages

### CMD Frame (Raspberry Pi → ESP32)
```json
{
  "type": "CMD",
  "seq": 1,
  "ts": 1234567890,
  "data": {
    "joints": [90, 90, 90, 90, ..., 90],
    "speed": 25
  }
}
```
- `seq`: Sequence number (0–65535)
- `ts`: Timestamp in milliseconds (from monotonic clock on RPi)
- `joints`: Array of 18 float angles (0°–180°)
- `speed`: Speed parameter (currently unused by ESP32)

### ACK Frame (ESP32 → Raspberry Pi)
```json
{
  "type": "ACK",
  "seq": 1,
  "ts": 1234567890,
  "data": {
    "status": "OK",
    "applied": 18
  }
}
```
- `seq`: Echoed sequence number for correlation
- `applied`: Number of servo commands successfully applied (18 if successful)

### ERR Frame (ESP32 → Raspberry Pi)
```json
{
  "type": "ERR",
  "seq": 1,
  "data": {
    "code": "BAD_SIZE",
    "msg": "Need 18 joints, get 15"
  }
}
```

**Error codes:**
- `BAD_JSON`: Malformed JSON or parse error
- `BAD_SIZE`: Joint array size ≠ 18
- `BAD_ANGLE`: Servo angle outside 0–180° range

---

## File Structure

### ESP32 Code
- `main.ino`: Setup and FreeRTOS task creation
- `config.ino`: Pin and I2C address definitions
- `protocol.ino`: Command parsing, validation, and frame handlers
- `HexLeg.ino`: Servo motion control with smooth interpolation
- `positions.ino`: Predefined leg position constants

### Raspberry Pi Code
- `main.py`: Command loop sending random angles with retry logic
- `protocol.py`: UART protocol class with JSON frame encoding/decoding

---

## Running the Protocol

### ESP32
Upload the sketch using Arduino IDE or PlatformIO:
```bash
pio run -t upload
```

Serial monitor output (115200 baud):
```
ESP32 UART Protocol Ready
Angles [ 90.00,90.00,90.00,...]
send ACK seq: 1
```

### Raspberry Pi
```bash
python3 main.py
```

Output:
```
Attempt 1
Success! seq:1 received!
Attempt 1
Success! seq:2 received!
...
```

---

## Servo Control Flow

1. Raspberry Pi sends CMD with 18 joint angles
2. ESP32 parses JSON and validates each angle (0–180°)
3. ESP32 applies angles to PCA9685 via `leg.smoothTo()`
4. Servo motors move with smooth 30-step interpolation over 300ms
5. ESP32 sends ACK if successful, ERR if validation fails
6. Raspberry Pi retries up to 3 times on timeout or ERR

---

## Communication Parameters

- **Baud rate**: 115200
- **Message format**: JSON + newline (`\n`)
- **Max retries**: 3 (Raspberry Pi side)
- **Timeout**: 0.5 seconds per command
- **Servo smooth steps**: 30 steps over 300ms (10ms per step)

---

## Notes

- Sequence numbers wrap at 65536 for long-running sessions
- All timestamps are in milliseconds
- ESP32 runs UART parsing in a high-priority FreeRTOS task
- Servo motion is blocking (frame parsing waits for motion to complete)
- No error recovery on ESP32; invalid commands are logged and rejected

---

## Troubleshooting

- **No ACK/ERR response**: Check UART2 pins (GPIO 4/5) and baudrate (115200)
- **"BAD_JSON" error**: Ensure JSON is valid and ends with newline
- **"BAD_SIZE" error**: Verify joint array has exactly 18 elements
- **Servos don't move**: Confirm PCA9685 I2C address (0x40) and power supply
- **Jerky motion**: Increase `smoothTo()` step count in `HexLeg.ino`
