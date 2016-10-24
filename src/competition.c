#pragma config(Sensor, dgtl1,  autoJumper,   sensorTouch)
#pragma config(Sensor, dgtl2,  ledRed,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  ledGreen,     sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  armSwitch,    sensorTouch)
#pragma config(Sensor, dgtl5,  leftEncoder,  sensorRotation)
#pragma config(Sensor, dgtl6,  rightEncoder, sensorRotation)
#pragma config(Sensor, dgtl7,  sideEncoder,  sensorRotation)
#pragma config(Motor,  port1,  rightMaster,  tmotorVex393_HBridge, openLoop, driveRight)
#pragma config(Motor,  port2,  rightSlave1,  tmotorVex393_MC29,    openLoop, driveRight)
#pragma config(Motor,  port3,  rightSlave2,  tmotorVex393_MC29,    openLoop, driveRight)
#pragma config(Motor,  port4,  leftSlave1,   tmotorVex393_MC29,    openLoop, driveLeft)
#pragma config(Motor,  port5,  leftSlave2,   tmotorVex393_MC29,    openLoop, driveLeft)
#pragma config(Motor,  port6,  leftMaster,   tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port8,  sideMotor,    tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port9,  armLeft,      tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port10, armRight,     tmotorVex393_HBridge, openLoop, driveLeft)
// Code automatically generated by 'ROBOTC' configuration wizard

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// Global Variables
bool isFlipped = false;         // Toggles which side is front
bool slowMode = false;          // Reduces speed by indicated percent
int slowModePercent = 4;        // Percent to reduce forward motion (Default 4)
int slowModePercentSide = 3;    // Percent to reduce sideways motion (Default 3)
int jsThreshold = 25; 					// Minimum amount for joystick register movement
int sidewaysForwardPercent = 6; // Percent to move forward when going sideways (Default 6)
unsigned int loopCount = 0;     // Debug output counter

// SECTION: Movement Functions

/**
 * Left motors movement control.
 * Sets the value of the left motors in normal mode or right motors in flipped
 * mode; Speed is divided by slowModePercent if in slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtForwardLeft(signed char speed) {
  if (slowMode) { speed = speed / slowModePercent; }

  if (!isFlipped) {
    motor[leftMaster] = -speed;
  } else {
    motor[rightMaster] = -speed;
  }
}

/**
 * Right motors movement control.
 * Sets the value of the right motors in normal mode or left motors in flipped
 * mode; Speed is divided by slowModePercent if in slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtForwardRight(signed char speed) {
  if (slowMode) { speed = speed / slowModePercent; }

  if (!isFlipped) {
    motor[rightMaster] = speed;
  } else {
    motor[leftMaster] = speed;
  }
}

/**
 * Left motors movement control.
 * Sets the value of the side motors in normal mode; Value is negated in flipped
 * mode; Speed is divided by slowModePercentSide if in slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtSide(signed char speed) {
  if (isFlipped) { speed = -speed; }
  if (slowMode) { speed = speed / slowModePercentSide; }

  if (speed < 0) {
    if (!isFlipped) {
      int fwdSpeed = motor[leftMaster] - (speed / sidewaysForwardPercent);

      if (fwdSpeed <= 0) {
        motor[leftMaster] = fwdSpeed;
      } else {
        motor[leftMaster] = -127;
      }
    } else {
      int fwdSpeed = motor[rightMaster] - (speed / sidewaysForwardPercent);

      if (fwdSpeed <= 0) {
        motor[rightMaster] = fwdSpeed;
      } else {
        motor[rightMaster] = -127;
      }
    }
  } else if (speed > 0) {
    if (!isFlipped) {
      int fwdSpeed = motor[rightMaster] + (speed / sidewaysForwardPercent);

      if (fwdSpeed >= 0) {
        motor[rightMaster] = fwdSpeed;
      } else {
        motor[rightMaster] = 127;
      }
    } else {
      int fwdSpeed = motor[leftMaster] + (speed / sidewaysForwardPercent);

      if (fwdSpeed >= 0) {
        motor[leftMaster] = fwdSpeed;
      } else {
        motor[leftMaster] = 127;
      }
    }
  }

  motor[sideMotor] = speed;
}

/**
 * High hang motors movement control.
 * Sets the value of the high hang motors in normal mode; Value is not effected
 * by flipped mode or slow mode
 *
 * @param speed Speed in range -127 to 127
 */
void mvtHighHang(signed char speed) {
  if (speed < 0 && SensorValue(armSwitch) != 0) {
    motor[armLeft] = 0;
    motor[armRight] = 0;
  } else {
    motor[armLeft] = speed;
    motor[armRight] = -speed;
  }
}

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
    if (isFlipped) { SensorValue[ledRed] = 1; } else { SensorValue[ledRed] = 0;	}
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
    if (slowMode) { SensorValue[ledGreen] = 1; } else { SensorValue[ledGreen] = 0;	}
  }
}

/**
 * Controls the speed of the left and right motors.
 * Tests Ch3 for right motors and Ch2 for left motors; Does not activate movement
 * without joystick being over jsThreshold to prevent ghost movement
 */
void ctlJoysticks() {
  if (vexRT[Ch3] <= -jsThreshold || vexRT[Ch3] >= jsThreshold) {
    mvtForwardRight(vexRT[Ch3]);
  } else {
    mvtForwardRight(0);
  }

  if (vexRT[Ch2] <= -jsThreshold || vexRT[Ch2] >= jsThreshold) {
    mvtForwardLeft(vexRT[Ch2]);
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

/**
 * Logs the state of the motors.
 * Writes to the Debug Stream in a comma-seperated formatted list
 */
void logState() {
  if (loopCount == 0) {   // Prints the dubug header on first output
    writeDebugStreamLine("loopCount,leftMotor,rightMotor,sideMotor,highHang,slowMode,isFlipped");
  }

  writeDebugStream("%i", loopCount);
  writeDebugStream(",%i",motor[leftMaster]);
  writeDebugStream(",%i", motor[rightMaster]);
  writeDebugStream(",%i",motor[sideMotor]);
  writeDebugStream(",%i",motor[armLeft]);
  writeDebugStream(",%d",slowMode);
  writeDebugStreamLine(",%d",isFlipped);

  loopCount++;
}

/**
 * Pre-Autonomous Functions.
 * Includes all activities that occur before the competition starts; Turns the
 * leds off and sets up the slave motors.
 */
void pre_auton() {
  bStopTasksBetweenModes = true;

  // Slave Motors
  slaveMotor(leftSlave2, leftMaster);
  slaveMotor(leftSlave1, leftMaster);

  slaveMotor(rightSlave2, rightMaster);
  slaveMotor(rightSlave1, rightMaster);

  // Turn off LEDs
  SensorValue[ledRed] = 0;
  SensorValue[ledGreen] = 0;
}

/**
 * Autonomous Task.
 */
task autonomous() {
  // Insert user code here.

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/**
 * User Control Task.
 */
task usercontrol() {
  while (true) {
    logState();
    ctlFlipSides();
    ctlSlowMode();
    ctlJoysticks();
    ctlSideMovement();
    ctlHighHang();
  }
}
