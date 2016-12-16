// SECTION: Status Functions

#include "main.h"

// Global Variables
short allFlashCount = 0;
short redFlashCount = 0;
short yellowFlashCount = 0;
short greenFlashCount = 0;
bool pretest = false;

/**
 * Stores the amount to the corresponding flashCount variable.
 */
void stat_flashLeds(int amt) {
  allFlashCount = amt;
}

/**
 * Stores the amount to the corresponding flashCount variable.
 */
void stat_flashLedRed(int amt) {
  redFlashCount = amt;
}

/**
 * Stores the amount to the corresponding flashCount variable.
 */
void stat_flashLedYellow(int amt) {
  yellowFlashCount = amt;
}

/**
 * Stores the amount to the corresponding flashCount variable.
 */
void stat_flashLedGreen(int amt) {
  greenFlashCount = amt;
}

/**
 * Enables the LED Pretest after initialization of the LED Controller Task
 */
void stat_doLedPretest() {
  pretest = true;
}

/**
 * Resets LEDs.
 * Sets the state of the red, yellow, and green leds based upon the values of the
 * slowMode, locked, and lockingMode, respectfully.
 */
void stat_resetLeds() {
  SensorValue[ledRed] = (slowMode ? 1 : 0);
  SensorValue[ledYellow] = (locked ? 1 : 0);
  SensorValue[ledGreen] = (lockingMode ? 1 : 0);

}

/**
 * Flashes the LEDs.
 * Turns the LEDs on and off based upon the values of the allFlashCount variable
 * with 50ms delay in between each cycle
 */
void stat_localFlashLeds() {
  for (int i=0; i<allFlashCount; i++) {
    SensorValue[ledYellow] = 1;
    SensorValue[ledRed] = 1;
    SensorValue[ledGreen] = 1;
    wait1Msec(50);
    SensorValue[ledYellow] = 0;
    SensorValue[ledRed] = 0;
    SensorValue[ledGreen] = 0;
    wait1Msec(50);
  }

  allFlashCount = 0;
  stat_resetLeds();
}

/**
 * Flashes the red LED.
 * Turns the red LED on and off based upon the values of the redFlashCount variable
 * with 50ms delay in between each cycle
 */
void stat_localFlashLedRed() {
  for (int i=0; i<redFlashCount; i++) {
    SensorValue[ledRed] = 1;
    wait1Msec(50);
    SensorValue[ledRed] = 0;
    wait1Msec(50);
  }

  redFlashCount = 0;
}

/**
 * Flashes the yellow LED.
 * Turns the yellow LED on and off based upon the values of the yellowFlashCount
 * variable with 50ms delay in between each cycle
 */
void stat_localFlashLedYellow() {
  for (int i=0; i<yellowFlashCount; i++) {
    SensorValue[ledYellow] = 1;
    wait1Msec(50);
    SensorValue[ledYellow] = 0;
    wait1Msec(50);
  }

  yellowFlashCount = 0;
}

/**
 * Flashes the green LED.
 * Turns the green LED on and off based upon the values of the greenFlashCount
 * variable with 50ms delay in between each cycle
 */
void stat_localFlashLedGreen() {
  for (int i=0; i<greenFlashCount; i++) {
    SensorValue[ledGreen] = 1;
    wait1Msec(50);
    SensorValue[ledGreen] = 0;
    wait1Msec(50);
  }

  greenFlashCount = 0;
}

/**
 * Turns the LEDs on and off in a pattern.
 * Preforms visual LED test and indicates the start of a task.
 */
void stat_localDoLedPretest() {
  redFlashCount = 3;
  yellowFlashCount = 3;
  greenFlashCount = 3;
  stat_localFlashLedRed();
  stat_localFlashLedYellow();
  stat_localFlashLedGreen();
  SensorValue[ledGreen] = 1;
  wait1Msec(250);

  pretest = false;
}

/**
 * Handles Execution of flashCount Variables.
 */
bool stat_localExecuteFlashCount() {
  if (allFlashCount > 0) {
    stat_localFlashLeds();
    return true;
  }

  if (redFlashCount > 0) {
    stat_localFlashLedRed();
    return true;
  }

  if (yellowFlashCount > 0) {
    stat_localFlashLedYellow();
    return true;
  }

  if (greenFlashCount > 0) {
    stat_localFlashLedGreen();
    return true;
  }
  return false;
}

/**
 * LED controller.
 * Handles ticking of the LEDs without devoting time away from the main loop.
 */
void stat_ledController() {
  if (pretest) {
    stat_localDoLedPretest();
  }

  stat_resetLeds();
  stat_localExecuteFlashCount();
}
