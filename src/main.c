#pragma config(UserModel, "motor_setup.h")
#include "Vex_Competition_Includes.c"
#include "constants.h"
#include "status.c"
#include "motors.c"
#include "movement.c"
#include "autonomous.c"
#include "control.c"

/**
 * Pre-Autonomous Functions.
 * Includes all activities that occur before the competition starts; Turns the
 * leds off and sets up the slave motors.
 */
void pre_auton() {
  bStopTasksBetweenModes = true;

  // Set LEDs to correct values
  stat_flashLeds(6);
}

/**
 * Autonomous Task.
 */
task autonomous() {
  int distSideMvt = 10;
  int autonSpeed = (SensorValue[autonJumper] ? -65 : 65);

  atn_mvtFwdSnr(40, 127, false);
  // wait1Msec(250);
  // 9mvtAutonSide(distSideMvt * 1.2, autonSpeed);
  for (int i=0; i<3; i++) {
    wait1Msec(250);
    atn_mvtStar();
    atn_mvtSideSnr(distSideMvt * 2, -autonSpeed, false);
  }

  /*
  for (int i=0; i<10; i++) {
    mvtAutonStar();
    mvtAutonSide(distSideMvt, autonSpeed);
  }
  */
}

/**
 * User Control Task.
 */
task usercontrol() {
  while (true) {
    // Avoid Linear and freeform movement in same cycle
    if (!ctl_testJoystickleft()) {
      ctl_testJoystickRight();
    }

    // Avoid Linear and freeform rotation in same cycle
    if (!ctl_testRotationSegments()) {
      ctl_testRotationFree();
    }

    ctl_testSlowMode();
    ctl_testHighHang();

    mtr_doMotorTick();
    wait1Msec(10);
  }
}
