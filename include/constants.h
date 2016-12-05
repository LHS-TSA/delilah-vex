#ifndef DELILAH_CONSTANTS_H
#define DELILAH_CONSTANTS_H

#define SLOW_MAX_SPEED 32        // Speed to rescale for slow mode (Default 32)
#define JOYSTICK_THRESHOLD 25 	 // Minimum amount for joystick register movement
#define TIME_ONE_INCH 58         // Milliseconds to spin for one inch at half speed
#define TIME_ONE_SEGMENT -1      // Milliseconds to rotate for 45 degrees
#define TIME_ONE_DEGREE -1       // Centiseconds that count towards a degree of rotation
#define MOTOR_ZERO_SPEED 5       // Jumps to skip when zeroing motors

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

#define JOY_LX vexRT[Ch4]
#define JOY_LY vexRT[Ch3]
#define JOY_RX vexRT[Ch1]
#define JOY_RY vexRT[Ch2]

#endif // DELILAH_CONSTANTS_H
