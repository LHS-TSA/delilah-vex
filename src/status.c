// SECTION: Status Functions

#include "main.h"
#include "constants.h"

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
  digitalWrite(LED_RED, (slowMode ? 1 : 0));
  digitalWrite(LED_YELLOW, 0);
  digitalWrite(LED_GREEN, 0);
}

/**
 * Flashes the LEDs.
 * Turns the LEDs on and off based upon the values of the allFlashCount variable
 * with 50ms delay in between each cycle
 */
void stat_localFlashLeds() {
  for (int i=0; i<allFlashCount; i++) {
    digitalWrite(LED_RED, 1);
    digitalWrite(LED_YELLOW, 1);
    digitalWrite(LED_GREEN, 1);
    taskDelay(50);
    digitalWrite(LED_RED, 0);
    digitalWrite(LED_YELLOW, 0);
    digitalWrite(LED_GREEN, 0);
    taskDelay(50);
  }

  allFlashCount = 0;
  stat_resetLeds();
}

/**
 * Flashes the red LED.
 * Turns the red LED on and off based upon the values of the redFlashCount variable
 * with 50ms delay in between each cycle; This code is really redundant but pointers
 * are confusing and copy-pasting is easier than learning how to actually do it
 * correctly
 */
void stat_localFlashLedRed() {
  for (; redFlashCount>0; redFlashCount--) {
    digitalWrite(LED_RED, 1);
    taskDelay(50);
    digitalWrite(LED_RED, 0);
    taskDelay(50);
  }
}

/**
 * Flashes the yellow LED.
 * Turns the yellow LED on and off based upon the values of the yellowFlashCount
 * variable with 50ms delay in between each cycle; This code is really redundant
 * but pointers are confusing and copy-pasting is easier than learning how to
 * actually do it correctly
 */
void stat_localFlashLedYellow() {
  for (; yellowFlashCount>0; yellowFlashCount--) {
    digitalWrite(LED_YELLOW, 1);
    taskDelay(50);
    digitalWrite(LED_YELLOW, 0);
    taskDelay(50);
  }
}

/**
 * Flashes the green LED.
 * Turns the green LED on and off based upon the values of the greenFlashCount
 * variable with 50ms delay in between each cycle; This code is really redundant
 * but pointers are confusing and copy-pasting is easier than learning how to
 * actually do it correctly
 */
void stat_localFlashLedGreen() {
  for (; greenFlashCount>0; greenFlashCount--) {
    digitalWrite(LED_GREEN, 1);
    taskDelay(50);
    digitalWrite(LED_GREEN, 0);
    taskDelay(50);
  }
}

/**
 * Turns the LEDs on and off in a pattern.
 * Preforms visual LED test and indicates the start of a task.
 */
void stat_localDoLedPretest() {
  redFlashCount = 3;
  stat_localFlashLedRed();

  yellowFlashCount = 3;
  stat_localFlashLedYellow();

  digitalWrite(LED_GREEN, 1);
  taskDelay(250);

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
void stat_ledController(void* argseee) {
  while (true) {
    if (pretest) {
      stat_localDoLedPretest();
    }

    stat_resetLeds();
    stat_localExecuteFlashCount();
    taskDelay(100);
  }
}
