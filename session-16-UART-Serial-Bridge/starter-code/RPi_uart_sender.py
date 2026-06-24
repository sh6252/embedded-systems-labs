#!/usr/bin/env python3

import serial
import time

ser = serial.Serial(
        port = '/dev/serial0',
        baudrate = 115200,
        bytesize = serial.EIGHTBITS,
        parity = serial.PARITY_NONE,
        stopbits = serial.STOPBITS_ONE,
        timeout = 1
)

print("UART open: ", ser.name)
time.sleep(2)

try:
        while True:
                msg = "HELLO FROM RPI\n"
                ser.write(msg.encode('utf-8'))
                print(f"Sent: {msg.strip()}")

                if ser.in_waiting > 0:
                        response = ser.readline().decode('utf-8').strip()
                        print(f"ESP32 replied: {response}")
                time.sleep(1)
except KeyboardInterrupt:
        ser.close()

