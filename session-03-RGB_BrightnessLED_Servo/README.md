# RGB, Brightness LED & Servo 🎨🤖

A cute and colorful project that combines:
- keypad control
- RGB LED control
- breathing brightness LED
- servo movement to a selected angle

What happens here:
- keys 1-9 build a number for the servo angle
- `#` confirms the entered angle
- `A/B/C` set different RGB colors
- `D` resets everything and returns the servo to 90°

Recommended hardware:
- MicroPython board
- RGB pins on `GPIO4`, `GPIO5`, `GPIO6`
- breathing LED on `GPIO10`
- servo on `GPIO14`
- 4x4 keypad on [13,12,11,8] and [18,17,16,15]

How to use:
1. Copy the file to your MicroPython environment.
2. Run `main.py`.
3. Press keypad buttons and watch the colors and servo move.

Why it is cute:
- It feels like a little magic keypad that sends commands by touch.
- RGB changes smoothly and dynamically.
- The servo moves precisely to the angle you enter.

A fun, colorful maker project! 🌈
