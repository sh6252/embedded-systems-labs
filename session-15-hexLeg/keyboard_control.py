import time
import keyboard
from positions import POSITIONS

def keyboard_loop(leg):

    print("Controls:")
    print("W=Lift S=Stand A=Retract D=Extend H=Home")
    print("C=Crouch T=Stretch B=Balance")
    print("Q/E=Hip rotate")

    while True:

        if keyboard.is_pressed("w"):
            leg.smooth_to(POSITIONS["LIFT"])

        elif keyboard.is_pressed("s"):
            leg.smooth_to(POSITIONS["STAND"])

        elif keyboard.is_pressed("a"):
            leg.smooth_to(POSITIONS["RETRACT"])

        elif keyboard.is_pressed("d"):
            leg.smooth_to(POSITIONS["EXTEND"])

        elif keyboard.is_pressed("h"):
            leg.smooth_to(POSITIONS["HOME"])

        elif keyboard.is_pressed("c"):
            leg.smooth_to(POSITIONS["CROUCH"])

        elif keyboard.is_pressed("t"):
            leg.smooth_to(POSITIONS["STRETCH"])

        elif keyboard.is_pressed("b"):
            leg.smooth_to(POSITIONS["BALANCE"])

        elif keyboard.is_pressed("q"):
            leg.rotate_hip(-5)

        elif keyboard.is_pressed("e"):
            leg.rotate_hip(5)

        time.sleep(0.05)