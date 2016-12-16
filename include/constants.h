#ifndef DELILAH_CONSTANTS_H
#define DELILAH_CONSTANTS_H

#define SLOW_MAX_SPEED 60         // Speed to rescale for slow mode (Default 32)
#define JOYSTICK_THRESHOLD 25 	  // Minimum amount for joystick register movement
#define DEGREES_ONE_SEGMENT 200   // Milliseconds to rotate for 45 degrees
#define BTN_TOGGLE_TIMEOUT 250    // Time to wait after toggling buttons

// Motor Correction
#define MAX_MOTOR_A 127
#define MAX_MOTOR_B 127
#define MAX_MOTOR_C 127
#define MAX_MOTOR_D 127

// Starting Box Coordinates
#define LEFT_BOX_X 20
#define RIGHT_BOX_X 80

// Motor index numbers
#define MOTOR_A 2
#define MOTOR_B 3
#define MOTOR_C 4
#define MOTOR_D 5
#define MOTOR_LEFT_LOW 6
#define MOTOR_RIGHT_LOW 7
#define MOTOR_LEFT_HIGH 8
#define MOTOR_RIGHT_HIGH 9

// Joystick Controls
#define JOY_LX 0,4                // Joystick Left, Left-Right
#define JOY_LY 0,3                // Joystick Left, Up-Down
#define JOY_RX 0,1                // Joystick Right, Left-Right
#define JOY_RY 0,2                // Joystick Right, Up-Down

// Left Buttons
#define L_BTN_RIGHT 0,7,JOY_RIGHT
#define L_BTN_LEFT 0,7,JOY_LEFT
#define L_BTN_UP 0,7,JOY_UP
#define L_BTN_DOWN 0,7,JOY_DOWN

// Right Buttons
#define R_BTN_RIGHT 0,7,JOY_RIGHT
#define R_BTN_LEFT 0,7,JOY_LEFT
#define R_BTN_UP 0,7,JOY_UP
#define R_BTN_DOWN 0,7,JOY_DOWN

// L and R Buttons
#define TL_BTN_DOWN 0,6,JOY_DOWN
#define TR_BTN_DOWN 0,5,JOY_DOWN
#define TL_BTN_UP 0,6,JOY_UP
#define TR_BTN_UP 0,5,JOY_UP

// LEDs
#define LED_RED 9
#define LED_YELLOW 10
#define LED_GREEN 11

// Global Variables
#define STARTING_BOX digitalRead(20) // Digital Port 12, I think
#define BUMPER_ARM digitalRead(9)    // Digital Port 1, I think
extern bool slowMode;

#endif // DELILAH_CONSTANTS_H
