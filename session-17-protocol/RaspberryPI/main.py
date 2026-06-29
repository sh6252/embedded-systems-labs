#!/usr/bin/env python3

import serial
import random
import time
from protocol import UART_protocol

ser = serial.Serial("/dev/serial0", 115200)
prot = UART_protocol(ser)

angles = [90] * 18

while True:
    

    # Send servo command with retry logic
    if prot.send_with_retry(angles):
        angles = [random.randint(0, 180) for _ in range(18)]

    time.sleep(1)
