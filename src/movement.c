// SECTION: Movement Functions

#include "main.h"
#include "constants.h"
#include "motors.h"

/**
 * Trim and adjust speed.
 * Lowers given speed value to between -127 and 127.
 *
 * @param speed Speed
 * @param slow Scale speed for slow mode
 */
short mvt_localTrimSpeed(short speed) {
  if (speed > 127) { speed %= 127; }
  if (speed < -127) { speed = -(speed % 127); }
  return speed;
}

/**
 * Variable length rotation movement.
 * Calculates and sets the motor speeds so that the robot rotates about its center;
 * Speed is rescaled by the mvt_localTrimSpeed function before calling the motors'
 * functions but is not affected by slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvt_setRotationSpeed(short speed) {
  // speed = mvt_localTrimSpeed(speed, false);
  botVelocityZ = speed;
}

/**
 * Arm motor control.
 * Sets the value of the arm motors in normal mode; Speed is rescaled by the
 * mvt_localTrimSpeed function before calling the motors' functions but is not
 * affected by slow mode; Motors will not activate if descending and the arm
 * bumper is depressed
 *
 * @param speed Speed in range -127 to 127
 */
void mvt_setArmSpeed(short speed) {
  speed = mvt_localTrimSpeed(speed);

  if (speed < 0 && BUMPER_ARM) {
    motorSet(MOTOR_LEFT_LOW, 0);
    motorSet(MOTOR_LEFT_HIGH, 0);
    motorSet(MOTOR_RIGHT_LOW, 0);
    motorSet(MOTOR_RIGHT_HIGH, 0);
  } else {
    motorSet(MOTOR_LEFT_LOW, -speed);
    motorSet(MOTOR_LEFT_HIGH, -speed);
    motorSet(MOTOR_RIGHT_LOW, speed);
    motorSet(MOTOR_RIGHT_HIGH, speed);
  }
}
