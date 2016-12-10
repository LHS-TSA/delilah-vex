// SECTION: Status Functions

short allFlashCount = 0;
short redFlashCount = 0;
short yellowFlashCount = 0;
short greenFlashCount = 0;

void stat_flashLeds(int amt) {
  allFlashCount = amt;
}

void stat_flashLedRed(int amt) {
  redFlashCount = amt;
}

void stat_flashLedYellow(int amt) {
  yellowFlashCount = amt;
}

void stat_flashLedGreen(int amt) {
  greenFlashCount = amt;
}

/**
 * Resets LEDs.
 * Turns the green led on if the robot is in slow mode and turns the red led on
 * if the current front of robot is the push-bar side
 */
void stat_resetLeds() {
  SensorValue[ledRed] = (slowMode ? 1 : 0);
  SensorValue[ledYellow] = (locked ? 1 : 0);
  SensorValue[ledGreen] = (lockingMode ? 1 : 0);

}

void stat_localFlashLeds() {
  for (int i=0; i<allFlashCount; i++) {
    SensorValue[ledYellow] = 1;
    SensorValue[ledRed] = 1;
    wait1Msec(50);
    SensorValue[ledYellow] = 0;
    SensorValue[ledRed] = 0;
    wait1Msec(50);
  }

  allFlashCount = 0;
  stat_resetLeds();
}

void stat_localFlashLedRed() {
  for (int i=0; i<redFlashCount; i++) {
    SensorValue[ledRed] = 1;
    wait1Msec(50);
    SensorValue[ledRed] = 0;
    wait1Msec(50);
  }

  redFlashCount = 0;
}

void stat_localFlashLedYellow() {
  for (int i=0; i<yellowFlashCount; i++) {
    SensorValue[ledYellow] = 1;
    wait1Msec(50);
    SensorValue[ledYellow] = 0;
    wait1Msec(50);
  }

  yellowFlashCount = 0;
}

void stat_localFlashLedGreen() {
  for (int i=0; i<greenFlashCount; i++) {
    SensorValue[ledGreen] = 1;
    wait1Msec(50);
    SensorValue[ledGreen] = 0;
    wait1Msec(50);
  }

  greenFlashCount = 0;
}

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

task stat_ledController() {
  bool flash = false;

  while (true) {
    clearTimer(T2);              // Resets timer to 0
    stat_resetLeds();
    flash = stat_localExecuteFlashCount();

    // Make a cycle last exectly 50ms
    if (time1[T2] < 50) {
      while(time1[T2] < 50) { wait1Msec(1); }
    } else if (!flash) {
      writeDebugStreamLine("[WARN] LED Cycle Exceeded 50ms; Lasted %dms", time1(T2));
    }
  }
}
