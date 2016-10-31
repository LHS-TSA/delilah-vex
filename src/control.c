// SECTION: Controller Functions

/**
 * Controls when front side of robot is swapped.
 * Tests for presses to Btn8D and flips the bool value isFlipped when activated;
 * The red led will be active when in flipped mode
 */
void ctlFlipSides() {
  if (vexRT[Btn8D]) {
    wait1Msec(250);       // This is to keep button press from rapidly switching
    isFlipped = !isFlipped;
    statResetLeds();
  }
}

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to Btn8R and flips the bool value slowMode when activated;
 * The green led will be active when in slow mode
 */
void ctlSlowMode() {
  if (vexRT[Btn8R]) {
    wait1Msec(250);
    slowMode = !slowMode;
    statResetLeds();
  }
}

/**
 * Controls when the high hang protection is disabled.
 * Tests for presses to Btn8L and flips the bool value modeHighHang when activated;
 * The green led will blink if enabled and the red led will blink when disabled
 */
void ctlHighHangMode() {
  if (vexRT[Btn8L]) {
    modeHighHang = !modeHighHang;

    if (modeHighHang) {
      SensorValue[ledGreen] = 1;
      wait1Msec(62);
      SensorValue[ledGreen] = 0;
      wait1Msec(62);
      SensorValue[ledGreen] = 1;
      wait1Msec(62);
      SensorValue[ledGreen] = 0;
      wait1Msec(62);
    } else {
      SensorValue[ledRed] = 1;
      wait1Msec(62);
      SensorValue[ledRed] = 0;
      wait1Msec(62);
      SensorValue[ledRed] = 1;
      wait1Msec(62);
      SensorValue[ledRed] = 0;
      wait1Msec(62);
    }
    statResetLeds();
  }
}

/**
 * Controls the speed of the left and right motors.
 * Tests Ch3 for right motors and Ch2 for left motors; Does not activate movement
 * without joystick being over jsThreshold to prevent ghost movement
 */
void ctlJoysticks() {
    mvtForwardRight(vexRT[Ch3]);
  if (vexRT[Ch3] <= -JOYSTICK_THRESHOLD || vexRT[Ch3] >= JOYSTICK_THRESHOLD) {
  } else {
    mvtForwardRight(0);
  }

    mvtForwardLeft(vexRT[Ch2]);
  if (vexRT[Ch2] <= -JOYSTICK_THRESHOLD || vexRT[Ch2] >= JOYSTICK_THRESHOLD) {
  } else {
    mvtForwardLeft(0);
  }
}

/**
 * Controls the speed of the side motor.
 * Tests Btn6D and Bth5D for activation and sets speed to highest level for the
 * duration of their activation
 */
void ctlSideMovement() {
  if (vexRT[Btn6D]) {
    mvtSide(127);
  } else if (vexRT[Btn5D]) {
    mvtSide(-127);
  } else {
    mvtSide(0);
  }
}

/**
 * Controls the speed of the high hang motors.
 * Tests Btn7U and Btn7D for activation and sets speed to highest level for the
 * duration of their activation
 */
void ctlHighHang() {
  if (vexRT[Btn7U]) {
    mvtHighHang(127);
  } else if (vexRT[Btn7D]) {
    mvtHighHang(-127);
  } else {
    mvtHighHang(0);
  }
}
