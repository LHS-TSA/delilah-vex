/*
 * Stephen and John's Vex Robot Source
 */

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// Pre-Autonomous Functions
void pre_auton()
{
  bStopTasksBetweenModes = true;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// Autonomous Task
task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

// User Control Task
task usercontrol()
{
  while (true)
  {
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // Remove this function call once you have "real" code.
    UserControlCodePlaceholderForTesting();
  }
}
