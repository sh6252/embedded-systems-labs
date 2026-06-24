import time
import board
import busio
from adafruit_pca9685 import PCA9685

# I2C init
i2c = busio.I2C(board.SCL, board.SDA)

# PCA9685 init
pca = PCA9685(i2c)
pca.frequency = 50  # סרוו סטנדרטי

def angle_to_pwm(angle):
    # 0–180 -> duty cycle approx
    min_duty = 2000
    max_duty = 8000
    return int(min_duty + (angle / 180) * (max_duty - min_duty))

channel = 0

while True:
    for angle in [0, 90, 180]:
        pwm_value = angle_to_pwm(angle)
        pca.channels[channel].duty_cycle = pwm_value
        time.sleep(1)




