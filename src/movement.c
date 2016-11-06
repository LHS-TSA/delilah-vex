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
  if (speed > 127 || speed < -127) { speed %= 127; }

  if (slow) { speed /= SLOW_MAX_SPEED; }

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
 * Set straight forward movement.
 * Calculates and sets the motor speeds so that the net movement of the robot is
 * towards the middle boundary; Speed is rescaled by the mvt_localTrimSpeed
 * function before calling the motors' functions
 *
 * @param speed Speed in range -127 to 127
 */
void mvt_setSrtFwdSpeed(short speed) {
  speed = mvt_localTrimSpeed(speed);
  // TODO: straight forward movement
}

/**
 * Set straight sideways movement.
 * Calculates and sets the motor speeds so that the net movement of the robot is
 * towards the right boundary; Speed is rescaled by the mvt_localTrimSpeed
 * function before calling the motors' functions
 *
 * @param speed Speed in range -127 to 127
 */
void mvt_setSrtSideSpeed(short speed) {
  speed = mvt_localTrimSpeed(speed);
  // TODO: straight sideways movement
}

/**
 * High hang motor control.
 * Sets the value of the high hang motors in normal mode; Speed is rescaled by
 * the mvt_localTrimSpeed function before calling the motors' functions but is
 * not affected by slow mode; Motors will not activate if decending and the arm
 * bumper is depressed
 *
 * @param speed Speed in range -127 to 127
 */
void mvt_setHighHang(short speed) {
  speed = mvt_localTrimSpeed(speed, false)

  if (speed < 0 && (SensorValue(armSwitch)) {
    motor[armLeft] = 0;
    motor[armRight] = 0;
  } else {
    motor[armLeft] = speed;
    motor[armRight] = -speed;
  }
}
