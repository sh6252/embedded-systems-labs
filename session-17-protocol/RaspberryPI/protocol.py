import json
import time

class UART_protocol:

    def __init__(self, serial_port):
        self.ser = serial_port
        self.seq = 0

    def _next_seq(self):
        self.seq = (self.seq + 1) % 65536
        return self.seq

    def send_cmd(self, joints_deg, speed=25):
        """Send 18 joint angles to ESP32."""

        frame = {
            "type": "CMD",
            "seq": self._next_seq(),
            "ts": int(time.monotonic() * 1000),
            "data": {
                "joints": joints_deg,
                "speed": speed
            }
        }

        line = json.dumps(frame) + "\n"
        self.ser.write(line.encode("utf-8"))
        return frame["seq"]

    def read_reply(self, timeout=0.5):
        """Read one ACK or ERR from ESP32."""
        
        self.ser.timeout = timeout
        raw = self.ser.readline().decode("utf-8").strip()
        if not raw: return None
        return json.loads(raw)

    
    def send_with_retry(self, angles, speed=25):
        max_retries = 3

        for attempt in range(max_retries):
            print(f"Attempt {attempt+1}")

            seq = self.send_cmd(angles, speed)

            reply = self.read_reply(timeout=0.5)

            if reply is None:
                    print("Timeout")
                    continue

            if reply['type'] == 'ACK' and reply['seq'] == seq:
                    print(f"Success! seq:{seq} received!")
                    time.sleep(0.05)
                    return True

            if reply['type'] == 'ERR':
                    print("ESP Error:", reply['data']['msg'])
                    continue

        print("FAILED")
        time.sleep(0.1)
        return False