// SECTION: Movement Functions

/**
 * Trim and adjust speed.
 * Lowers given speed value to between -127 and 127 and scales the speed to slow
 * mode if enabled.
 *
 * @param speed Speed
 * @param slow Scale speed for slow mode
 */
short mvt_localTrimSpeed(short speed, bool slow) {
  if (speed > 127) { speed %= 127; }
  if (speed < -127) { speed = -(speed % 127); }

  if (slow) { speed = (speed * SLOW_MAX_SPEED) / 127; }

  return speed;
}

/**
 * Trim and adjust speed.
 * Lowers given speed value to between -127 and 127 and scales the speed to slow
 * mode if the global variable "slowMode" it true.
 *
 * @param speed Speed
 */
short mvt_localTrimSpeed(short speed) {
  return mvt_localTrimSpeed(speed, slowMode);
}

/**
 * Toggles Lock.
 */
bool mvt_toggleLock() {
  if (locked) {
    motor[lockServo] = -127;
    locked = false;
  } else {
    motor[lockServo] = 127;
    locked = true;
  }
  return locked;
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
  speed = mvt_localTrimSpeed(speed, false);

  if (speed < 0 && SensorValue(armSwitch)) {
    motor[armLeft] = 0;
    motor[armRight] = 0;
  } else {
    motor[armLeft] = -speed;
    motor[armRight] = speed;
  }
}
