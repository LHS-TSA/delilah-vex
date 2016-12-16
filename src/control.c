// SECTION: Controller Functions

#include "API.h"
#include "constants.h"
#include "motors.h"
#include "main.h"
#include "movement.h"

// Quick Controller Changing
#define BTN_SLOW L_BTN_RIGHT    // Toggles Slow Mode
#define BTN_ROT_NEG TL_BTN_DOWN // Free Rotation Counterclockwise
#define BTN_ROT_POS TR_BTN_DOWN // Free Rotation Clockwise
#define BTN_ARM_UP L_BTN_UP     // Extends Arm Up
#define BTN_ARM_DOWN L_BTN_DOWN // Retracts Arm Down

/**
 * Controls when motors are at reduced speed.
 * Tests for presses to BTN_SLOW and flips the bool value slowMode when activated;
 * The red led will be active when in slow mode
 *
 * @return true if the control was activated, false otherwise
 */
bool ctl_testSlowMode() {
  if (joystickGetDigital(BTN_SLOW)) {
    wait(BTN_TOGGLE_TIMEOUT);
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
  if (joystickGetAnalog(JOY_LY) <= -JOYSTICK_THRESHOLD || joystickGetAnalog(JOY_LY) >= JOYSTICK_THRESHOLD) {
    botVelocityY = joystickGetAnalog(JOY_LY);
    botVelocityX = 0;
    return true;
  }

  if (joystickGetAnalog(JOY_LX) <= -JOYSTICK_THRESHOLD || joystickGetAnalog(JOY_LX) >= JOYSTICK_THRESHOLD) {
    botVelocityX = joystickGetAnalog(JOY_LX);
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

  if (joystickGetAnalog(JOY_RY) <= -JOYSTICK_THRESHOLD || joystickGetAnalog(JOY_RY) >= JOYSTICK_THRESHOLD) {
    botVelocityY = joystickGetAnalog(JOY_RY);
    control = true;
  } else {
    botVelocityY = 0;
  }

  if (joystickGetAnalog(JOY_RX) <= -JOYSTICK_THRESHOLD || joystickGetAnalog(JOY_RX) >= JOYSTICK_THRESHOLD) {
    botVelocityX = joystickGetAnalog(JOY_RX);
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
  if (joystickGetDigital(BTN_ROT_NEG)) {
    mvt_setRotationSpeed(60);
    return true;
  }

  if (joystickGetDigital(BTN_ROT_POS)) {
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
  if (joystickGetDigital(BTN_ARM_UP)) {
    mvt_setArmSpeed(127);
    return true;
  } else if (joystickGetDigital(BTN_ARM_DN)) {
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
