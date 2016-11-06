// SECTION: Controller Functions

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to Btn8R and flips the bool value slowMode when activated;
 * The green led will be active when in slow mode
 *
 * @return true if the control was activated, false otherwise
 */
void ctl_testSlowMode() {
  if (vexRT[Btn8R]) {
    wait1Msec(250);
    slowMode = !slowMode;
    stat_resetLeds();
    return true;
  }
  return false;
}

/**
 * Controls the speed of the left and right motors.
 * Tests Ch3 for right motors and Ch2 for left motors; Does not activate movement
 * without joystick being over jsThreshold to prevent ghost movement
 */
void ctl_testJoysticks() {
  if (vexRT[Ch3] <= -JOYSTICK_THRESHOLD || vexRT[Ch3] >= JOYSTICK_THRESHOLD) {
    mvt_setForwardRight(vexRT[Ch3]);
  } else {
    mvt_setForwardRight(0);
  }

  if (vexRT[Ch2] <= -JOYSTICK_THRESHOLD || vexRT[Ch2] >= JOYSTICK_THRESHOLD) {
    mvt_setForwardLeft(vexRT[Ch2]);
  } else {
    mvt_setForwardLeft(0);
  }
}

/**
 * Controls the speed of the side motor.
 * Tests Btn6D and Bth5D for activation and sets speed to highest level for the
 * duration of their activation
 */
void ctl_testSideMovement() {
  if (vexRT[Btn6D]) {
    mvt_setSide(127);
  } else if (vexRT[Btn5D]) {
    mvt_setSide(-127);
  } else {
    mvt_setSide(0);
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
  if (vexRT[Btn7U]) {
    mvt_setHighHang(127);
    return true;
  } else if (vexRT[Btn7D]) {
    mvt_setHighHang(-127);
    return true;
  } else {
    mvt_setHighHang(0);
    return false;
  }
}
