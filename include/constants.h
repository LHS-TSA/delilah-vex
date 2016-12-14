#ifndef DELILAH_CONSTANTS_H
#define DELILAH_CONSTANTS_H

#define SLOW_MAX_SPEED 60         // Speed to rescale for slow mode (Default 32)
#define JOYSTICK_THRESHOLD 25 	  // Minimum amount for joystick register movement
#define TIME_ONE_INCH 58          // Milliseconds to spin for one inch at half speed
#define TIME_ONE_SEGMENT 200      // Milliseconds to rotate for 45 degrees
#define TIME_ONE_DEGREE -1        // Centiseconds that count towards a degree of rotation
#define MOTOR_ZERO_SPEED 5        // Jumps to skip when zeroing motors
#define BTN_TOGGLE_TIMEOUT 250    // Time to wait after toggling buttons

// Motor Correction
#define MAX_MOTOR_A 127
#define MAX_MOTOR_B 127
#define MAX_MOTOR_C 127
#define MAX_MOTOR_D 127

// Shorthand for motors
#define MOTOR_A motor[motorA]
#define MOTOR_B motor[motorB]
#define MOTOR_C motor[motorC]
#define MOTOR_D motor[motorD]

#define JOY_LX vexRT[Ch4]         // Joystick Left, Left-Right
#define JOY_LY vexRT[Ch3]         // Joystick Left, Up-Down
#define JOY_RX vexRT[Ch1]         // Joystick Right, Left-Right
#define JOY_RY vexRT[Ch2]         // Joystick Right, Up-Down

#define BTN_SLOW vexRT[Btn7R]     // Toggles Slow Mode
#define BTN_LOCKING vexRT[Btn7L]  // Toggles Locking Mode
#define BTN_ARM_UP vexRT[Btn7U]   // Extends arm up
#define BTN_ARM_DN vexRT[Btn7D]   // Retracts arm down

#define BTN_ROT_NEG vexRT[Btn6D]  // Free Rotation Counterclockwise
#define BTN_ROT_POS vexRT[Btn5D]  // Free Rotation Clockwise

#define BTN_SROT_NEG vexRT[Btn6U] // Segmented Rotation Counterclockwise
#define BTN_SROT_POS vexRT[Btn5U] // Segmented Rotation Clockwise

#define BTN_DEG_0 vexRT[Btn8U]    // Set rotation value to 0
#define BTN_DEG_90 vexRT[Btn8R]   // Set rotation value to 90
#define BTN_DEG_180 vexRT[Btn8D]  // Set rotation value to 180
#define DTN_DEG_270 vexRT[Btn8L]  // Set rotation value to 270

#endif // DELILAH_CONSTANTS_H
