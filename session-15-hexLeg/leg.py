import time

class HexLeg:
    def __init__(self, kit, hip_ch=0, fem_ch=1, tib_ch=2):

        self.kit = kit

        self.servos = {
            "hip": kit.servo[hip_ch],
            "femur": kit.servo[fem_ch],
            "tibia": kit.servo[tib_ch]
        }

        self.current = {"hip": 90, "femur": 90, "tibia": 90}

    def set_angles(self, hip, femur, tibia):
        self.servos["hip"].angle = hip
        self.servos["femur"].angle = femur
        self.servos["tibia"].angle = tibia

        self.current = {"hip": hip, "femur": femur, "tibia": tibia}

    def move_to(self, position):
        self.set_angles(*position)

    def smooth_to(self, position, steps=30, delay=0.01):

        target = {"hip": position[0], "femur": position[1], "tibia": position[2]}
        start = self.current

        for i in range(1, steps + 1):

            h = start["hip"] + (target["hip"] - start["hip"]) * i / steps
            f = start["femur"] + (target["femur"] - start["femur"]) * i / steps
            t = start["tibia"] + (target["tibia"] - start["tibia"]) * i / steps

            self.set_angles(h, f, t)
            time.sleep(delay)

    def rotate_hip(self, delta):
        self.set_angles(
            self.current["hip"] + delta,
            self.current["femur"],
            self.current["tibia"]
        )