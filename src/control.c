// SECTION: Controller Functions

#include "API.h"
#include "constants.h"

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to BTN_SLOW and flips the bool value slowMode when activated;
 * The red led will be active when in slow mode
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
 * Tests JOY_LY for forward motion and then JOY_LX for sideways movement; Both
 * forward and sideways motion cannot be used at the same time - forward takes
 * priority; Does not activate movement without joystick being over joystick
 * threshold to prevent ghost movement
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
 * Tests JOY_RY for forward motion and then JOY_RX for sideways movement; Both
 * forward and sideways can be used at the same time; Does not activate movement
 * without joystick being over joystick threshold to prevent ghost movement
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
 * Controls freeform rotation.
 * Tests BTN_ROT_NEG and BTN_ROT_POS for activation and rotates the robot.
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testRotationFree() {
  if (BTN_ROT_NEG) {
    mvt_setRotationSpeed(60);
    return true;
  }

  if (BTN_ROT_POS) {
    mvt_setRotationSpeed(-60);
    return true;
  }

  mvt_setRotationSpeed(0);
  return false;
}

/**
 * Controls the speed of the high hang motors.
 * Tests BTN_ARM_UP and BTN_ARM_DN for activation and sets speed to highest level
 * for the duration of their activation
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

/**
 * Tests the controllers for input change.
 * See child functions for more detailed discriptions of tasks.
 */
void ctl_doControllerTick() {
  // Avoid different movement types in same cycle
  bool botMoved = false;

  if (!botMoved) { botMoved = ctl_testJoystickleft(); }
  if (!botMoved) { botMoved = ctl_testJoystickRight(); }
  if (!botMoved) { botMoved = ctl_testRotationFree(); }

  // if (!botMoved) { botMoved = ctl_testRotationSegments(); }

  ctl_testSlowMode();
  ctl_testHighHang();
}
