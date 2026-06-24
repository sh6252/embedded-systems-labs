from adafruit_servokit import ServoKit

kit = ServoKit(channels=16, address=0x40)

kit.servo[0].set_pulse_width_range(500, 2500)

while True:
    user_input = input("Enter angle 0-180, or q to quit: ")

    if user_input.lower() == "q":
        break

    try:
        angle = int(user_input)
    except ValueError:
        print("Error: enter a number")
        continue

    if angle < 0 or angle > 180:
        print("Error: angle must be between 0 and 180")
        continue

    kit.servo[0].angle = angle
    print(f"Servo moved to {angle}")