// SECTION: Controller Functions

/**
 * Controls when front side of robot is swapped.
 * Tests for presses to Btn8D and flips the bool value isFlipped when activated;
 * The red led will be active when in flipped mode
 */
void ctl_testFlipSides() {
  if (vexRT[Btn8D]) {
    wait1Msec(250);       // This is to keep button press from rapidly switching
    isFlipped = !isFlipped;
    stat_resetLeds();
  }
}

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to Btn8R and flips the bool value slowMode when activated;
 * The green led will be active when in slow mode
 */
void ctl_testSlowMode() {
  if (vexRT[Btn8R]) {
    wait1Msec(250);
    slowMode = !slowMode;
    stat_resetLeds();
  }
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
 */
void ctl_testHighHang() {
  if (vexRT[Btn7U]) {
    mvt_setHighHang(127);
  } else if (vexRT[Btn7D]) {
    mvt_setHighHang(-127);
  } else {
    mvt_setHighHang(0);
  }
}
