#pragma config(UserModel, "motor_setup.h")

#include "Vex_Competition_Includes.c"
#include "constants.h"

// Global Variables
bool slowMode = false;              // Reduces speed by indicated percent
bool locked = false;
bool lockingMode = false;

#include "status.c"
#include "motors.c"
#include "movement.c"
// #include "autonomous.c"
#include "control.c"

/**
 * Pre-Autonomous Functions.
 * Includes all activities that occur before the competition starts; Turns the
 * leds off and sets up the slave motors.
 */
void pre_auton() {
  bStopTasksBetweenModes = true;
  motor[lockServo] = -127;

  // Set LEDs to correct values
  stat_flashLeds(6);
}

/**
 * Autonomous Task.
 *
 */
task autonomous() {
	/*
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
  clearTimer(T1);

  while (true) {
    // Avoid different movement types in same cycle
    bool botMoved = false;

    if (!botMoved) { botMoved = ctl_testJoystickleft(); }
    if (!botMoved) { botMoved = ctl_testJoystickRight(); }
    // if (!botMoved) { botMoved = ctl_testRotationSegments(); }
    if (!botMoved) { botMoved = ctl_testRotationFree(); }

    ctl_testSlowMode();
    ctl_testHighHang();
    ctl_testLock();
    mtr_doMotorTick();

    // Make a cycle last exectly 20ms
    if (time1[T1] < 20) {
      while(time1[T1] < 20) { wait1Msec(1); }
      mtr_commitMotorSpeeds();
      clearTimer(T1);              // Resets timer to 0
    } else {
      writeDebugStreamLine("[WARN] Cycle Exceeded 20ms; Lasted %d", time1(T1));
      clearTimer(T1);
    }
  }
}
