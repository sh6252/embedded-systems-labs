#ifndef POSITIONS_INO
#define POSITIONS_INO
enum PositionId {
  HOME,
  STAND,
  LIFT,
  EXTEND,
  RETRACT,
  CROUCH,
  STRETCH,
  BALANCE,
  POS_COUNT
};

struct Position {
  float joints[3];
};

const Position POSITIONS[POS_COUNT] = {
  {90, 90, 90},     // HOME
  {90, 110, 70},    // STAND
  {90, 60, 90},     // LIFT
  {60, 90, 90},     // EXTEND
  {120, 90, 90},    // RETRACT
  {90, 140, 40},    // CROUCH
  {90, 70, 130},    // STRETCH
  {100, 100, 80}    // BALANCE
};

#endif

