// SECTION: Autonomous Movement

/**
 * Autonomous forward encoder movement control.
 * Controls the motion of the motors using the motor encoders during an
 * autonomous period
 *
 * @param dist Distance to move forward in inches
 * @param speed Speed in range -127 to 127
 */
void atn_mvtFwdEnc(int dist, signed char speed) {
  if (speed == 0) { return; }

  SensorValue[leftEncoder] = 0;
  SensorValue[rightEncoder] = 0;

  dist *= TIME_ONE_INCH;

  mvt_setForwardLeft(speed);
  mvt_setForwardRight(speed);

  wait1Msec(dist);              // Remove once encoders work

  mvt_setForwardLeft(0);
  mvt_setForwardRight(0);
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
void atn_mvtFwdSnr(int dist, signed char speed, bool relative) {
  if (speed == 0) { return; }

  if (SensorValue[sonarFront] == -1) {    // If sensor is messed up
    stat_flashLeds(4);

    atn_mvtFwdEnc(65, speed);
    return;
  }

  if (relative) {
    dist += SensorValue[sonarFront];
  }

  while (SensorValue[sonarFront] < dist) {
    mvt_setForwardLeft(speed);
    mvt_setForwardRight(speed);
  }

  mvt_setForwardLeft(0);
  (0);
}

/**
 * Autonomous sideways movement control.
 * Controls the motion of the sideways motors during an autonomous period
 *
 * @param dist Distance to move forward in inches
 * @param speed Speed in range -127 to 127
 */
void atn_mvtSide(int dist, signed char speed) {
  dist *= TIME_ONE_INCH;

  mvt_setSide(speed);
  wait1Msec(dist);
  mvt_setSide(0);

  /*
  if (speed > 0) {
   mvtForwardRight(127);
   wait1Msec(50);               // Sideways correction timing
   mvtForwardRight(0);
  } else {
   mvtForwardLeft(127);
   wait1Msec(50);               // Sideways correction timing
   mvtForwardLeft(0);
  }
  */
}

 /**
  * Autonomous star knocking movement control.
  * Controls the high hang bar during the autonomous period; Extends arm, moves
  * back, retracts arm, and returns to initial position
  */
void atn_mvtStar() {
  // Extend Arm
  mvt_setHighHang(127);
  wait1Msec(1250);               // High hang upwards duration
  mvt_setHighHang(0);

  // Move back so doesn't climb fence
    mvt_setForwardLeft(-65);
    mvt_setForwardRight(-65);
    wait1Msec(100);               // High hang shift duration
    mvt_setForwardLeft(0);
    mvt_setForwardRight(0);

  // Lower arm
  while (SensorValue[armSwitch] == 0) {
    mvt_setHighHang(-65);
  }
  mvt_setHighHang(0);

  // Return to position
  mvt_setForwardLeft(65);
  mvt_setForwardRight(65);
  wait1Msec(120);               // High hang return shift duration
  mvt_setForwardLeft(0);
  mvt_setForwardRight(0);
}
