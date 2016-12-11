// SECTION: Controller Functions

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to Btn8R and flips the bool value slowMode when activated;
 * The green led will be active when in slow mode
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testLock() {
  if (BTM_LOCKING) {
    wait1Msec(BTN_TOGGLE_TIMEOUT);
    lockingMode = !lockingMode;
    return true;
  }

  if (lockingMode && SensorValue(armSwitch)) {
    mvt_toggleLock();
    lockingMode = false;
    return true;
  }
  return false;
}

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to Btn8R and flips the bool value slowMode when activated;
 * The green led will be active when in slow mode
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testSlowMode() {
  if (BTN_SLOW) {
    wait1Msec(BTN_TOGGLE_TIMEOUT);
    slowMode = !slowMode;
    return true;
  }
  return false;
}

/**
 * Controls Linear Motion.
 * Tests Ch3 for forward motion and then Ch4 for sideways movement; Both forward
 * and sideways motion cannot be used at the same time - forward takes priority;
 * Does not activate movement without joystick being over joystick threshold to
 * prevent ghost movement
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testJoystickleft() {
  if (JOY_LY <= -JOYSTICK_THRESHOLD || JOY_LY >= JOYSTICK_THRESHOLD) {
    botVelocityY = JOY_LY;
    botVelocityX = 0;
    return true;
  }

  if (JOY_LX <= -JOYSTICK_THRESHOLD || JOY_LX >= JOYSTICK_THRESHOLD) {
    botVelocityX = JOY_LX;
    botVelocityY = 0;
    return true;
  }

  botVelocityX = 0;
  botVelocityY = 0;
  return false;
}

/**
 * Controls Freeform Motion.
 * Tests Ch1 for forward motion and then Ch2 for sideways movement; Both forward
 * and sideways can be used at the same time; Does not activate movement without
 * joystick being over joystick threshold to prevent ghost movement
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testJoystickRight() {
  bool control = false;

  if (JOY_RY <= -JOYSTICK_THRESHOLD || JOY_RY >= JOYSTICK_THRESHOLD) {
    botVelocityY = JOY_RY;
    control = true;
  } else {
    botVelocityY = 0;
  }

  if (JOY_RX <= -JOYSTICK_THRESHOLD || JOY_RX >= JOYSTICK_THRESHOLD) {
    botVelocityX = JOY_RX;
    control = true;
  } else {
    botVelocityX = 0;
  }

  return control;
}

/**
 * Controls rotation in segments.
 * Tests Btn6D and Bth5D for activation and rotates the robot by 45 degrees.
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testRotationSegments() {
  if (BTN_SROT_NEG) {
    mvt_rotateOneSegment(127, 1);
    return true;
  } else if (BTN_SROT_POS) {
    mvt_rotateOneSegment(-127, 1);
    return true;
  }

  return false;
}

/**
 * Controls freeform rotation.
 * Tests Btn6D and Bth5D for activation and rotates the robot by 45 degrees.
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testRotationFree() {
  if (BTN_ROT_NEG) {
    mvt_setRotationSpeed(127);
    return true;
  } else if (BTN_ROT_POS) {
    mvt_setRotationSpeed(-127);
    return true;
  }

  mvt_setRotationSpeed(0);
  return false;
}

bool ctl_testNetRotation() {
  if (BTN_DEG_0) {
    botRotation = 0;
    wait1Msec(BTN_TOGGLE_TIMEOUT);
    return true;
  } else if (BTN_DEG_90) {
    botRotation = 90;
    wait1Msec(BTN_TOGGLE_TIMEOUT);
    return true;
  } else if (BTN_DEG_180) {
    botRotation = 180;
    wait1Msec(BTN_TOGGLE_TIMEOUT);
    return true;
  } else if (DTN_DEG_270) {
    botRotation = 270;
    wait1Msec(BTN_TOGGLE_TIMEOUT);
    return true;
  } else {
    mvt_setRotationSpeed(0);
    return false;
  }
}


/**
 * Controls the speed of the high hang motors.
 * Tests Btn7U and Btn7D for activation and sets speed to highest level for the
 * duration of their activation
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testHighHang() {
  if (BTN_ARM_UP) {
    mvt_setArmSpeed(127);
    return true;
  } else if (BTN_ARM_DN) {
    mvt_setArmSpeed(-127);
    return true;
  } else {
    mvt_setArmSpeed(0);
    return false;
  }
}
