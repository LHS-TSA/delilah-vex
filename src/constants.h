#ifndef DELILAH_CONSTANTS_H
#define DELILAH_CONSTANTS_H

#define SLOW_PERCENT 4           // Percent to reduce forward motion (Default 4)
#define SLOW_SIDE_PERCENT 3      // Percent to reduce sideways motion (Default 3)
#define JOYSTICK_THRESHOLD 25 	 // Minimum amount for joystick register movement
#define SHAFT_CYCLE 392          // Shaft encoder value at one revolution
#define SHAFT_ONE_INCH 31        // Shaft encoder value at one inch at half speed
#define TIME_ONE_INCH 58         // Miliseconds to spin for one inch at half speed
#define MOTOR_CORRECTION 111		 // Percent to decrease left motors

#endif // DELILAH_CONSTANTS_H
