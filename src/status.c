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
