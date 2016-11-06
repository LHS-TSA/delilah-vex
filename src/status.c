// SECTION: Status Functions

/**
 * Resets LEDs.
 * Turns the green led on if the robot is in slow mode and turns the red led on
 * if the current front of robot is the push-bar side
 */
void stat_resetLeds() {
  SensorValue[ledRed] = 0;      // (isFlipped ? 0 : 1)
  SensorValue[ledGreen] = (slowMode ? 1 : 0);
}

void stat_flashLeds(int amt) {
  for (int i=0; i<amt; i++) {
    SensorValue[ledGreen] = 1;
    SensorValue[ledRed] = 1;
    wait1Msec(50);
    SensorValue[ledGreen] = 0;
    SensorValue[ledRed] = 0;
    wait1Msec(50);
  }

  stat_resetLeds();
}

void stat_flashLedRed(int amt) {
  for (int i=0; i<amt; i++) {
    // SensorValue[ledGreen] = 1;
    SensorValue[ledRed] = 1;
    wait1Msec(50);
    // SensorValue[ledGreen] = 0;
    SensorValue[ledRed] = 0;
    wait1Msec(50);
  }

  stat_resetLeds();
}

void stat_flashLedGreen(int amt) {
  for (int i=0; i<amt; i++) {
    SensorValue[ledGreen] = 1;
    // SensorValue[ledRed] = 1;
    wait1Msec(50);
    SensorValue[ledGreen] = 0;
    // SensorValue[ledRed] = 0;
    wait1Msec(50);
  }

  stat_resetLeds();
}
