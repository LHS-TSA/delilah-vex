// SECTION: Status Functions

/**
 * Resets LEDs.
 * Turns the green led on if the robot is in slow mode and turns the red led on
 * if the current front of robot is the push-bar side
 */
void statResetLeds() {
  SensorValue[ledRed] = (isFlipped ? 0 : 1);
  SensorValue[ledGreen] = (slowMode ? 1 : 0);
}

void statFlashLeds(int amt) {
  for (int i=0; i<amt; i++) {
    SensorValue[ledGreen] = 1;
    SensorValue[ledRed] = 1;
    wait1Msec(50);
    SensorValue[ledGreen] = 0;
    SensorValue[ledRed] = 0;
    wait1Msec(50);
  }

  statResetLeds();
}
