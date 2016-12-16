// SECTION: Drive Motor Control

#include "API.h"
#include "constants.h"
#include <math.h>

/**
 * Global Variables.
 * X and Y as described as (0,0)
 */
int botPosX;
int botPosY;

short botVelocityX = 0;               // Velocity relative to x-coordinate in xy-coordinate plane
short botVelocityY = 0;               // Velocity relative to y-coordinate in xy-coordinate plane
short botVelocityZ = 0;               // Rotation

short botRotationX = 0;               // Facing x-coordinate in xy-coordinate plane
short botRotationY = 0;               // Facing y-coordinate in xy-coordinate plane

short motorSpeeds[4] = {0, 0, 0, 0};  // Speed of each motor ()

short botAngle = 0;                   // angle of the robot
short botSpeed = 0;                   // speed of the robot
short botRotation = 0;                // rotation of the robot

/**
 * Return the speed of the non-facing motor speed.
 * Does fancy math things to get the speed of the opposing motors in such that
 * the full speed motors are offset to correctly match the povided degree.
 *
 * @param degree Degree of the direction of the robot's movement
 * @return 0.00031 * degree^3 + -0.041828 * degree^2 + 4.05596*degree + -126.037
 */
short mtr_localGetNonFacingMotorSpeed(int degree) {
  // TODO: OPTIMIZE ME!
  int deg_sq = degree * degree;
  int deg_cu = deg_sq * degree;

  float deg_sqf = -0.041828 * deg_sq;
  float deg_cuf = 0.00031 * deg_cu;
  float deg_f = 4.05596 * degree;

  return (short)(deg_sqf + deg_cuf + deg_f + -126.037);
}

/**
 * Get the quadrant of the current movement vector
 * @return Quadrant
 */
short mtr_localGetCurrentQuad() {
  // TODO: Make these more specific
  if (botVelocityY >= 0) {
    return (botVelocityX > 0 ? 1 : 2);
  } else {
    return (botVelocityX > 0 ? 4 : 3);
  }
}

/**
 * Generates the motor speeds for Quadrant 1
 */
void mtr_localQuad1() {
  short nfm = mtr_localGetNonFacingMotorSpeed(botAngle);

  motorSpeeds[0] = (nfm * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (-MAX_MOTOR_B * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (-nfm * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (MAX_MOTOR_D * botSpeed) / MAX_MOTOR_D;
}

/**
 * Generates the motor speeds for Quadrant 2
 */
void mtr_localQuad2() {
  short nfm = mtr_localGetNonFacingMotorSpeed(botAngle - 90);

  motorSpeeds[0] = (MAX_MOTOR_A * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (nfm * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (-MAX_MOTOR_C * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (-nfm * botSpeed) / MAX_MOTOR_D;
}

/**
 * Generates the motor speeds for Quadrant 3
 */
void mtr_localQuad3() {
  short nfm = -mtr_localGetNonFacingMotorSpeed(-botAngle - 90);

  motorSpeeds[0] = (-nfm * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (MAX_MOTOR_B * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (nfm * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (-MAX_MOTOR_D * botSpeed) / MAX_MOTOR_D;
}

/**
 * Generates the motor speeds for Quadrant 4
 */
void mtr_localQuad4() {
  short nfm = -mtr_localGetNonFacingMotorSpeed(-botAngle);

  motorSpeeds[0] = (-MAX_MOTOR_A * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (-nfm * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (MAX_MOTOR_C * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (nfm * botSpeed) / MAX_MOTOR_D;
}

/**
 * Calculates the angle and speed of the robot based upon the x and y velocities.
 */
void mtr_localCalcVelocity() {
  botAngle = (short)(atan2(botVelocityY, botVelocityX) * 57.2958);
  botSpeed = sqrt(botVelocityX * botVelocityX + botVelocityY * botVelocityY);
}

/**
 * Generates the motor speeds during a rotation event
 */
void mtr_localRotation() {
  motorSpeeds[0] = botVelocityZ;
  motorSpeeds[1] = botVelocityZ;
  motorSpeeds[2] = botVelocityZ;
  motorSpeeds[3] = botVelocityZ;
}

void mtr_localMotorSpeed() {
  if (!isAutonomous()) { mtr_localCalcVelocity(); }

  switch (mtr_localGetCurrentQuad()) {
    case 4: mtr_localQuad4(); break;
    case 3: mtr_localQuad3(); break;
    case 2: mtr_localQuad2(); break;
    default: mtr_localQuad1();
  }
}

void mtr_doMotorTick() {
  if (botVelocityZ != 0) {
    mtr_localRotation();
  } else {
    mtr_localMotorSpeed();
  }
}

void mtr_commitMotorSpeeds() {
  if (slowMode) {
    motorSet(MOTOR_A, (motorSpeeds[0] * SLOW_MAX_SPEED) / 127);
    motorSet(MOTOR_B, (motorSpeeds[1] * SLOW_MAX_SPEED) / 127);
    motorSet(MOTOR_C, (motorSpeeds[2] * SLOW_MAX_SPEED) / 127);
    motorSet(MOTOR_D, (motorSpeeds[3] * SLOW_MAX_SPEED) / 127);
  } else {
    motorSet(MOTOR_A, motorSpeeds[0]);
    motorSet(MOTOR_B, motorSpeeds[1]);
    motorSet(MOTOR_C, motorSpeeds[2]);
    motorSet(MOTOR_D, motorSpeeds[3]);
  }
}
