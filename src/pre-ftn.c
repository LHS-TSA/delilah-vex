#pragma config(Sensor, dgtl2,  ledRed,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  ledGreen,       sensorLEDtoVCC)
#pragma config(Motor,  port1,           rightFront,    tmotorVex393_HBridge, openLoop, driveRight)
#pragma config(Motor,  port2,           rightMid,      tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           rightBack,     tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           leftMid,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           leftBack,      tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           armRight,      tmotorNone, openLoop)
#pragma config(Motor,  port7,           armLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           sideMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftFront,     tmotorVex393_HBridge, openLoop, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	//Slave Motors
	slaveMotor(leftBack, leftFront);
	slaveMotor(leftMid, leftFront);

	slaveMotor(rightBack, rightFront);
	slaveMotor(rightMid, rightFront);

  // Direction Flipping
	bool isFlipped = false;
	SensorValue[ledRed] = 0;
	SensorValue[ledGreen] = 0;

	while (true) {

		// Flip sides
		while (vexRT[Btn8D]) {
			wait1Msec(250);
			isFlipped = !isFlipped;

			if (isFlipped) {
			  SensorValue[ledRed] = 1;
			} else {
			  SensorValue[ledRed] = 0;
			}
		}

    // Handles Flipped Sides
		if (isFlipped) { // High Hang Mode

      // Joysticks
			if (vexRT[Ch3] <= -20 || vexRT[Ch3] >= 20) {
				motor[leftFront] = vexRT[Ch3];
				} else {
				motor[leftFront] = 0;
			}

			if (vexRT[Ch2] <= -20 || vexRT[Ch2] >= 20) {
				motor[rightFront] = -vexRT[Ch2];
				} else {
				motor[rightFront] = 0;
			}

      // Side Movement
      while(vexRT[Btn6D]) { motor[sideMotor] = -127; }
      while(vexRT[Btn5D]) { motor[sideMotor] = 127; }
      motor[sideMotor] = 0;

		} else { // Normal Mode

      // Joysticks
			if (vexRT[Ch3] <= -20 || vexRT[Ch3] >= 20) {
				motor[rightFront] = vexRT[Ch3];
			} else {
				motor[rightFront] = 0;
			}

			if (vexRT[Ch2] <= -20 || vexRT[Ch2] >= 20) {
				motor[leftFront] = -vexRT[Ch2];
			} else {
				motor[leftFront] = 0;
			}

      // Side Movement
      while(vexRT[Btn6D]) { motor[sideMotor] = 127; }
      while(vexRT[Btn5D]) { motor[sideMotor] = -127; }
      motor[sideMotor] = 0;
		}

    while(vexRT[Btn7U]) {
      motor[armLeft] = 127;
      motor[armRight] = -127;
    }
    while(vexRT[Btn7D]) {
      motor[armLeft] = -127;
      motor[armRight] = 127;
    }

    motor[armLeft] = 0;
    motor[armRight] = 0;

	}
}
