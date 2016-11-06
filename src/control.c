// SECTION: Controller Functions

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to Btn8R and flips the bool value slowMode when activated;
 * The green led will be active when in slow mode
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testSlowMode() {
  if (vexRT[Btn8R]) {
    wait1Msec(250);
    slowMode = !slowMode;
    stat_resetLeds();
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
  if (vexRT[Ch3] <= -JOYSTICK_THRESHOLD || vexRT[Ch3] >= JOYSTICK_THRESHOLD) {
    // TODO: straight forward movement
    return true;
  }

  if (vexRT[Ch4] <= -JOYSTICK_THRESHOLD || vexRT[Ch4] >= JOYSTICK_THRESHOLD) {
    // TODO: straight sideways movement
    return true;
  }

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

  if (vexRT[Ch1] <= -JOYSTICK_THRESHOLD || vexRT[Ch1] >= JOYSTICK_THRESHOLD) {
    // TODO: freeform straight forward movement
    control = true;
  }

  if (vexRT[Ch2] <= -JOYSTICK_THRESHOLD || vexRT[Ch2] >= JOYSTICK_THRESHOLD) {
    // TODO: freeform sideways movement
    control = true;
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
  if (vexRT[Btn6D]) {
    mvt_rotateOneSegment(127, 1);
    return true;
  } else if (vexRT[Btn5D]) {
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
  if (vexRT[Btn6D]) {
    mvt_setRotationSpeed(127);
    return true;
  } else if (vexRT[Btn5D]) {
    mvt_setRotationSpeed(-127);
    return true;
  }

	mvt_setRotationSpeed(0);
  return false;
}

/**
 * Controls the speed of the high hang motors.
 * Tests Btn7U and Btn7D for activation and sets speed to highest level for the
 * duration of their activation
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testHighHang() {
  if (vexRT[Btn7U]) {
    mvt_setArmSpeed(127);
    return true;
  } else if (vexRT[Btn7D]) {
    mvt_setArmSpeed(-127);
    return true;
  } else {
    mvt_setArmSpeed(0);
    return false;
  }
}
