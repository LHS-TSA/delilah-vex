// SECTION: Autonomous Movement

/**
 * Relative sonar value.
 *
 * @param facing Position of sonar
 */
int atn_localGetSnr(short facing) {
  // TODO: Sonar value based on facing value
}

/**
 * Autonomous forward timed movement control.
 * Controls the motion of the motors for forward movement using the timing
 * during an autonomous period
 *
 * @param dist Distance to move forward in inches
 * @param speed Speed in range -127 to 127
 */
void atn_mvtFwdTime(int dist, short speed) {
  if (speed == 0) { return; }

  dist *= TIME_ONE_INCH;

  mvt_setSrtFwdSpeed(speed);
  wait1Msec(dist);
  mvt_setSrtFwdSpeed(0);
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
void atn_mvtFwdSnr(int dist, short speed, bool relative) {
  if (speed == 0) { return; }

  if (atn_localGetSnr(0) == -1) {    // If sensor is messed up
    stat_flashLeds(4);

    atn_mvtFwdTime(65, speed);
    return;
  }

  if (relative) {
    dist += atn_localGetSnr(0);
  }

  while (atn_localGetSnr(0) < dist) {
    mvt_setSrtFwdSpeed(speed);
  }

  mvt_setSrtFwdSpeed(0);
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

  mvt_setSrtSideSpeed(speed);
  wait1Msec(dist);

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
  mvt_setArmSpeed(127);
  wait1Msec(1250);               // High hang upwards duration
  mvt_setArmSpeed(0);

  // Move back so doesn't climb fence
    mvt_setSrtFwdSpeed(-65);
    wait1Msec(100);               // High hang shift duration
    mvt_setSrtFwdSpeed(0);

  // Lower arm
  while (SensorValue[armSwitch] == 0) {
    mvt_setArmSpeed(-65);
  }
  mvt_setArmSpeed(0);

  // Return to position
  mvt_setSrtFwdSpeed(65);
  wait1Msec(120);               // High hang return shift duration
  mvt_setSrtFwdSpeed(0);
}
