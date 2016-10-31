// SECTION: Movement Functions

/**
 * Left motors movement control.
 * Sets the value of the left motors in normal mode or right motors in flipped
 * mode; Speed is divided by slowModePercent if in slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtForwardLeft(signed char speed) {
  if (slowMode) { speed = speed / SLOW_PERCENT; }

  if (!isFlipped) {
    motor[leftMaster] = (-speed * MOTOR_CORRECTION) / 127;
  } else {
    motor[rightMaster] = -speed;
  }
}

/**
 * Right motors movement control.
 * Sets the value of the right motors in normal mode or left motors in flipped
 * mode; Speed is divided by slowModePercent if in slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtForwardRight(signed char speed) {
  if (slowMode) { speed = speed / SLOW_PERCENT; }

  if (!isFlipped) {
    motor[rightMaster] = speed;
  } else {
    motor[leftMaster] = (speed * MOTOR_CORRECTION) / 127;
  }
}

/**
 * Left motors movement control.
 * Sets the value of the side motors in normal mode; Value is negated in flipped
 * mode; Speed is divided by slowModePercentSide if in slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtSide(signed char speed) {
  if (isFlipped) { speed = -speed; }
  if (slowMode) { speed = speed / SLOW_SIDE_PERCENT; }

  motor[sideMotor] = speed;
}

/**
 * High hang motors movement control.
 * Sets the value of the high hang motors in normal mode; Value is not effected
 * by flipped mode or slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtHighHang(signed char speed) {
  if (speed < 0 && (SensorValue(armSwitch) && !modeHighHang)) {
    motor[armLeft] = 0;
    motor[armRight] = 0;
  } else {
    motor[armLeft] = speed;
    motor[armRight] = -speed;
  }
}
