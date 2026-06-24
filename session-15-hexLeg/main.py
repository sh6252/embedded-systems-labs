import time
from positions import POSITIONS
from adafruit_servokit import ServoKit
from leg import HexLeg
from keyboard_control import keyboard_loop

kit = ServoKit(channels=16)

leg = HexLeg(kit, hip_ch=0, fem_ch=1, tib_ch=2)


def step_cycle(leg, cycles=10, speed_factor=1.0):

    sequence = ["HOME", "LIFT", "EXTEND", "STAND", "RETRACT"]

    start_time = time.time()

    for _ in range(cycles):
        for state in sequence:
            leg.smooth_to(POSITIONS[state])
            time.sleep(0.4 * speed_factor)

    total = time.time() - start_time

    avg = total / cycles
    print(f"Avg cycle: {avg:.2f}s")
    print(f"Steps/min: {60/avg:.2f}")


def demo_custom_positions(leg):
    leg.smooth_to(POSITIONS["CROUCH"])
    leg.smooth_to(POSITIONS["BALANCE"])
    leg.smooth_to(POSITIONS["STRETCH"])

leg.smooth_to(POSITIONS["HOME"])

keyboard_loop(leg)