// SECTION: Autonomous Movement

#include "API.h"

/**
 * Autonomous forward timed movement control.
 * Controls the motion of the motors for forward movement using the timing
 * during an autonomous period
 *
 * @param duration Duration to move forward in miliseconds
 * @param x Horizontal speed in range -127 to 127
 * @param y Vertical speed in range -127 to 127
 * @param rot Degrees to rotate from current position
 */
void atn_mvtVelocityTimed(int duration, short x, short y, short rot) {
  // TODO: atn_mvtFwdVelocityTime
}

/**
 * Autonomous forward sonar movement control.
 * Controls the motion of the motors using the sonar thing I can't spell during an
 * autonomous period
 *
 * @param duration Time to move to location;
 *                 Minimum of time for max speed;
                   -1 for as quickly as possible
 * @param x X-coordinate relative to bottom-left being (0,0)
 * @param y Y-coordinate relative to bottom-left being (0,0)
 */
void atn_mvtToPosition(int duration, short x, short y) {
  // TODO: atn_mvtPosition
}
