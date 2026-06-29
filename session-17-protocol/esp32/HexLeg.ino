#ifndef HEXLEG_INO
#define HEXLEG_INO

#include "positions.ino"

class HexLeg {
private:
    Adafruit_PWMServoDriver* pca;

    int hip_ch;
    int femur_ch;
    int tibia_ch;

    float currentHip;
    float currentFemur;
    float currentTibia;

    const int SERVO_MIN = 102;   // 500µs  @ 50Hz
    const int SERVO_MAX = 512;   // 2500µs @ 50Hz


    void moveServo(int channel, float angle) {
        angle = constrain(angle, 0, 180);
        int pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
        pca->setPWM(channel, 0, pulse);
    }

public:
    HexLeg(Adafruit_PWMServoDriver* driver, int hip=0, int fem=1, int tib=2) {
        pca = driver;

        hip_ch = hip;
        femur_ch = fem;
        tibia_ch = tib;

        currentHip = 90;
        currentFemur = 90;
        currentTibia = 90;
    }

    void setAngles(float hip, float femur, float tibia) {
        moveServo(hip_ch, hip);
        moveServo(femur_ch, femur);
        moveServo(tibia_ch, tibia);

        currentHip = hip;
        currentFemur = femur;
        currentTibia = tibia;
    }

    void moveTo(const float position[3]) {
        setAngles(position[0], position[1], position[2]);
    }

    void smoothTo(const float position[3], int steps=30, int delayMs=10) {
        float targetHip = position[0];
        float targetFemur = position[1];
        float targetTibia = position[2];

        float startHip = currentHip;
        float startFemur = currentFemur;
        float startTibia = currentTibia;

        for (int i = 1; i <= steps; i++) {
            float h = startHip + (targetHip - startHip) * i / steps;
            float f = startFemur + (targetFemur - startFemur) * i / steps;
            float t = startTibia + (targetTibia - startTibia) * i / steps;

            setAngles(h, f, t);
            delay(delayMs);
        }
    }

    void home() {
        moveTo(POSITIONS[HOME].joints);
    }

    void stand() {
        moveTo(POSITIONS[STAND].joints);
    }

    void rotateHip(float delta) {
        setAngles(
            currentHip + delta,
            currentFemur,
            currentTibia
        );
    }
};

#endif