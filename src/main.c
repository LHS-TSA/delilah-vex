#pragma config(UserModel, "motor_setup.h")

#include "Vex_Competition_Includes.c"
#include "constants.h"

// Global Variables
bool slowMode = false;              // Reduces speed by indicated percent
bool locked = false;
bool lockingMode = false;
bool auton = false;

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
  stat_doLedPretest();

  bStopTasksBetweenModes = true;
  motor[lockServo] = -127;

  startTask(stat_ledController, 2);
}

/**
 * Autonomous Task.
 *
 */
task autonomous() {
  startTask(stat_ledController, 2);
  auton = true;
  // int distSideMvt = 10;
  int autonSpeed = (SensorValue[autonJumper] ? -127 : 127);

  // If on highhang side
    // go straight towards it
    // go at angle to get behind

  botVelocityX = autonSpeed;
  botVelocityY = autonSpeed / 2;
  mtr_doMotorTick();
  mtr_commitMotorSpeeds();

  mvt_setRotationSpeed(autonSpeed);
  mtr_doMotorTick();
  mtr_commitMotorSpeeds();

  mvt_setRotationSpeed(0);
}

/**
 * User Control Task.
 */
task usercontrol() {
  startTask(stat_ledController, 2);
  auton = false;

  while (true) {
    clearTimer(T1);              // Resets timer to 0
    // Avoid different movement types in same cycle
    bool botMoved = false;

    if (!botMoved) { botMoved = ctl_testJoystickleft(); }
    if (!botMoved) { botMoved = ctl_testJoystickRight(); }
    // if (!botMoved) { botMoved = ctl_testRotationSegments(); }
    if (!botMoved) { botMoved = ctl_testRotationFree(); }

    ctl_testSlowMode();
    ctl_testHighHang();
    ctl_testLock();
    ctl_testNetRotation();
    mtr_doMotorTick();

    // Make a cycle last exectly 20ms
    if (time1[T1] < 20) {
      while(time1[T1] < 20) { wait1Msec(1); }
      mtr_commitMotorSpeeds();
    } else {
      writeDebugStreamLine("[WARN] Main Cycle Exceeded 20ms; Lasted %dms", time1(T1));
    }
  }
}
