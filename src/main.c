#pragma config(UserModel, "motor_setup.h")

#include "Vex_Competition_Includes.c"
#include "constants.h"

// Global Variables
bool slowMode = false;          // Rescales speed to SLOW_MAX_SPEED
bool locked = false;            // Arm lock status
bool lockingMode = false;       // Auto engage arm lock
bool auton = false;             // Should motor tick calculate speed and direction

#include "status.c"
#include "motors.c"
#include "movement.c"
#include "autonomous.c"
#include "control.c"
#include "logger.c"

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
 */
task autonomous() {
  // TODO: Autonomous
}

/**
 * User Control Task.
 */
task usercontrol() {
  startTask(stat_ledController, 2);
  stat_flashLedGreen(3);
  motor[lockServo] = -127;
  auton = false;

  while (true) {
    clearTimer(T1);             // Resets timer to 0

    ctl_doControllerTick();     // Handles all controller processes
    mtr_doMotorTick();          // Fancy holonomic math stuff

    if (time1[T1] < 20) {       // Make a cycle last exectly 20ms
      while(time1[T1] < 20) { wait1Msec(1); }
      mtr_commitMotorSpeeds();
    } else {
      writeDebugStreamLine("[WARN] Main Cycle Exceeded 20ms; Lasted %dms", time1(T1));
    }
  }
}
