import uasyncio as asyncio
from machine import Pin, PWM

# =========================
# RGB
# =========================
red = PWM(Pin(4), freq=1000)
green = PWM(Pin(5), freq=1000)
blue = PWM(Pin(6), freq=1000)

def set_rgb(r, g, b):
    red.duty_u16(r)
    green.duty_u16(g)
    blue.duty_u16(b)

# =========================
# BREATHING LED
# =========================
breath = PWM(Pin(10), freq=1000)
breath_val = 0
breath_dir = 1

# =========================
# SERVO
# =========================
servo = PWM(Pin(14), freq=50)   

target_angle = 90

def servo_angle(angle):
    min_duty = 2000
    max_duty = 8000
    duty = int(min_duty + (angle / 180) * (max_duty - min_duty))
    servo.duty_u16(duty)

# =========================
# KEYPAD
# =========================
keys = [
    ['1','2','3','A'],
    ['4','5','6','B'],
    ['7','8','9','C'],
    ['*','0','#','D']
]

rows = [Pin(p, Pin.OUT) for p in [13,12,11,8]]
cols = [Pin(p, Pin.IN, Pin.PULL_DOWN) for p in [18,17,16,15]]

input_angle = ""
last_key = None

def scan():
    global last_key

    for r in range(4):
        rows[r].value(1)

        for c in range(4):
            if cols[c].value():

                key = keys[r][c]

                rows[r].value(0)

                # debounce: prevent double click
                if key == last_key:
                    return None

                last_key = key
                return key

        rows[r].value(0)

    last_key = None
    return None

# =========================
# KEYPAD TASK
# =========================
async def keypad_task():
    global input_angle, target_angle

    while True:
        key = scan()

        if key:
            print("KEY:", key)

            if key.isdigit():
                input_angle += key

            elif key == '#':
                if input_angle:
                    angle = int(input_angle)
                    if 0 <= angle <= 180:
                        target_angle = angle
                    input_angle = ""

            elif key == 'A':
                set_rgb(65535, 0, 0)

            elif key == 'B':
                set_rgb(0, 65535, 0)

            elif key == 'C':
                set_rgb(0, 0, 65535)

            elif key == 'D':
                set_rgb(0, 0, 0)
                target_angle = 90
                input_angle = ""

        await asyncio.sleep_ms(10)

# =========================
# SERVO TASK
# =========================
async def servo_task():
    global target_angle
    while True:
        servo_angle(target_angle)
        await asyncio.sleep_ms(50)

# =========================
# RGB TASK
# =========================
rgb_step = 0

async def rgb_task():
    global rgb_step

    while True:
        rgb_step = (rgb_step + 1500) % 65535
        set_rgb(rgb_step, 0, 65535 - rgb_step)

        await asyncio.sleep_ms(20)

# =========================
# BREATH TASK
# =========================
async def breath_task():
    global breath_val, breath_dir

    while True:
        breath_val += breath_dir * 2000

        if breath_val >= 65535:
            breath_val = 65535
            breath_dir = -1
        elif breath_val <= 0:
            breath_val = 0
            breath_dir = 1

        breath.duty_u16(breath_val)

        await asyncio.sleep_ms(15)

# =========================
# MAIN
# =========================
async def main():
    print("SYSTEM READY")

    asyncio.create_task(keypad_task())
    asyncio.create_task(rgb_task())
    asyncio.create_task(breath_task())
    asyncio.create_task(servo_task())

    while True:
        await asyncio.sleep(1)

asyncio.run(main())