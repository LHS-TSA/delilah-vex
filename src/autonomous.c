// SECTION: Autonomous Movement

/**
 * Autonomous forward encoder movement control.
 * Controls the motion of the motors using the motor encoders during an
 * autonomous period
 *
 * @param dist Distance to move forward in inches
 * @param speed Speed in range -127 to 127
 */
void mvtAutonFwdEnc(int dist, signed char speed) {
  if (speed == 0) { return; }

  SensorValue[leftEncoder] = 0;
  SensorValue[rightEncoder] = 0;

  dist *= shaftOneInch;

  while (SensorValue[leftEncoder] < dist && SensorValue[rightEncoder] < dist) {
    mvtForwardLeft(speed);
    mvtForwardRight(speed);
  }

  mvtForwardLeft(0);
  mvtForwardRight(0);
}

/**
 * Autonomous forward sonar movement control.
 * Controls the motion of the motors using the sonar thing I can't spell during an
 * autonomous period
 *
 * @param dist Distance to move forward in inches
 * @param speed Speed in range -127 to 127
 * @param relative add to current position
 */
void mvtAutonFwdSnr(int dist, signed char speed, bool relative) {
  if (speed == 0) { return; }

  if (SensorValue[sonarFront] == -1) {    // If sensor is messed up
    for (int i=0; i<4; i++) {
      SensorValue[ledGreen] = 1;
      SensorValue[ledRed] = 1;
      wait1Msec(25);
      SensorValue[ledGreen] = 0;
      SensorValue[ledRed] = 0;
      wait1Msec(25);
    }
    statResetLeds();

    mvtAutonFwdEnc(dist, speed);
    return;
  }

  if (relative) {
    dist += SensorValue[sonarFront];
  }

  while (SensorValue[sonarFront] < dist) {
    mvtForwardLeft(speed);
    mvtForwardRight(speed);
  }

  mvtForwardLeft(0);
  mvtForwardRight(0);
}

/**
 * Autonomous sideways movement control.
 * Controls the motion of the sideways motors during an autonomous period;
 * dist is in inches, speed is in range -+ 127
 *
 * @param dist Distance to move forward in inches
 * @param speed Speed in range -127 to 127
 */
void mvtAutonSide(int dist, signed char speed) {
  dist *= timeOneInch;

  mvtSide(speed);
  wait1Msec(dist);
  mvtSide(0);

  if (speed > 0) {
   mvtForwardRight(127);
   wait1Msec(50);               // Sideways correction timing
   mvtForwardRight(0);
  } else {
   mvtForwardLeft(127);
   wait1Msec(50);               // Sideways correction timing
   mvtForwardLeft(0);
  }
}

 /**
  * Autonomous star knocking movement control.
  * Controls the high hang bar during the autonomous period; Extends arm, moves
  * back, retracts arm, and returns to initial position
  */
void mvtAutonStar() {
  // Extend Arm
  mvtHighHang(127);
  wait1Msec(500);               // High hang upwards duration
  mvtHighHang(0);

  // Move back so doesn't climb fence
  mvtForwardLeft(-127);
  mvtForwardRight(-127);
  wait1Msec(200);               // High hang shift duration
  mvtForwardLeft(0);
  mvtForwardRight(0);

  // Lower arm
  while (SensorValue[armSwitch]) {
    mvtHighHang(-127);
  }
  mvtHighHang(0);

  // Return to position
  mvtForwardLeft(127);
  mvtForwardRight(127);
  wait1Msec(200);               // High hang return shift duration
  mvtForwardLeft(0);
  mvtForwardRight(0);
}
