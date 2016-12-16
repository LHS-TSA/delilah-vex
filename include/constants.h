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

// Motor index numbers
#define MOTOR_A 2
#define MOTOR_B 3
#define MOTOR_C 4
#define MOTOR_D 5
#define MOTOR_LEFT_LOW 6
#define MOTOR_RIGHT_LOW 7
#define MOTOR_LEFT_HIGH 8
#define MOTOR_RIGHT_HIGH 9

#define JOY_LX 0,4                // Joystick Left, Left-Right
#define JOY_LY 0,3                // Joystick Left, Up-Down
#define JOY_RX 0,1                // Joystick Right, Left-Right
#define JOY_RY 0,2                // Joystick Right, Up-Down

#define BTN_SLOW 0,7,JOY_RIGHT    // Toggles Slow Mode
#define BTN_LOCKING 0,7,JOY_LEFT  // Toggles Locking Mode
#define BTN_ARM_UP 0,7,JOY_UP     // Extends arm up
#define BTN_ARM_DN 0,7,JOY_DOWN   // Retracts arm down

#define BTN_ROT_NEG 0,6,JOY_DOWN  // Free Rotation Counterclockwise
#define BTN_ROT_POS 0,5,JOY_DOWN  // Free Rotation Clockwise

#define BTN_SROT_NEG 0,6,JOY_UP   // Segmented Rotation Counterclockwise
#define BTN_SROT_POS 0,5,JOY_UP   // Segmented Rotation Clockwise

#define BTN_DEG_0 0,8,JOY_UP      // Set rotation value to 0
#define BTN_DEG_90 0,8,JOY_RIGHT  // Set rotation value to 90
#define BTN_DEG_180 0,8,JOY_DOWN  // Set rotation value to 180
#define DTN_DEG_270 0,8,JOY_RIGHT // Set rotation value to 270

#endif // DELILAH_CONSTANTS_H
