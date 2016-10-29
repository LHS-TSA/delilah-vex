#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  autonJumper,  sensorTouch)
#pragma config(Sensor, dgtl2,  ledRed,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  ledGreen,     sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  sonarFront,   sensorSONAR_inch)
#pragma config(Sensor, dgtl6,  armSwitch,    sensorTouch)
#pragma config(Sensor, I2C_1,  leftEncoder,  sensorQuadEncoderOnI2CPort,   , AutoAssign)
#pragma config(Sensor, I2C_2,  rightEncoder, sensorQuadEncoderOnI2CPort,   , AutoAssign)
#pragma config(Motor,  port1,  rightMaster,  tmotorVex393_HBridge, openLoop, reversed, driveRight)
#pragma config(Motor,  port2,  rightSlave1,  tmotorVex393_MC29,    openLoop, driveRight)
#pragma config(Motor,  port3,  rightSlave2,  tmotorVex393_MC29,    openLoop, driveRight)
#pragma config(Motor,  port4,  leftSlave1,   tmotorVex393_MC29,    openLoop, driveLeft)
#pragma config(Motor,  port5,  leftSlave2,   tmotorVex393_MC29,    openLoop, driveLeft)
#pragma config(Motor,  port6,  leftMaster,   tmotorVex393_MC29,    openLoop, driveLeft)
#pragma config(Motor,  port7,  sideMotor,    tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port8,  armRight,     tmotorVex393_MC29,    openLoop, driveLeft)
#pragma config(Motor,  port9,  armLeft,      tmotorVex393_MC29,    openLoop)
// Code automatically generated by 'ROBOTC' configuration wizard

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

// Main competition background code
#include "Vex_Competition_Includes.c"

// Global Variables
bool isFlipped = false;         // Toggles which side is front
bool slowMode = false;          // Reduces speed by indicated percent
bool modeHighHang = false;			// Disables the motor protection on high hang
int slowModePercent = 4;        // Percent to reduce forward motion (Default 4)
int slowModePercentSide = 3;    // Percent to reduce sideways motion (Default 3)
int jsThreshold = 25; 					// Minimum amount for joystick register movement
int shaftFullCycle = 392;       // Shaft encoder value at one revolution
int shaftOneInch = 31;          // Shaft encoder value at one inch
int timeOneInch = 58;           // Miliseconds to spin for one inch
int MotorCorrection = 111;			// Percent to decrease left motors
unsigned int loopCount = 0;     // Debug output counter

// Include functions
#include "status.c"
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
  bStopTasksBetweenModes = true;

  // Slave Motors
  slaveMotor(leftSlave2, leftMaster);
  slaveMotor(leftSlave1, leftMaster);

  slaveMotor(rightSlave2, rightMaster);
  slaveMotor(rightSlave1, rightMaster);

  // Set LEDs to correct values
  statResetLeds();
}

/**
 * Autonomous Task.
 */
task autonomous() {
  int distSideMvt = 12;
  int autonSpeed = (SensorValue[autonJumper] ? -127 : 127);

  mvtAutonFwdSnr(55, 127, false);
  mvtAutonSide(distSideMvt * 1.5, autonSpeed);
  mvtAutonSide(distSideMvt * 1.5, autonSpeed);
  for (int i=0; i<4; i++) {
    mvtAutonStar();
    mvtAutonSide(distSideMvt * 1.5, autonSpeed);
  }
  for (int i=0; i<10; i++) {
    mvtAutonStar();
    mvtAutonSide(distSideMvt * 1.5, autonSpeed);
  }
}

/**
 * User Control Task.
 */
task usercontrol() {
  while (true) {
    // logState();
    ctlFlipSides();
    ctlSlowMode();
    ctlHighHangMode();
    ctlJoysticks();
    ctlSideMovement();
    ctlHighHang();
  }
}
