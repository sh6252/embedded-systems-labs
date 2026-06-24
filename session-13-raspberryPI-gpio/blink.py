from gpiozero import LED
from time import sleep

led = LED(17)

while True:
    led.on()
    print("led on...")
    sleep(1)
    led.off()
    print("led off...")
    sleep(1)
