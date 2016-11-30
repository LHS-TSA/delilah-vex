int deg(int x, int y) {
	int act = (int)(atan2(x,y) * 57);
	return round(act / 5) * 5;
}



task main() {
	while (true) {
		if (vexRT[Ch1] > 25 || vexRT[Ch2] > 25 || vexRT[Ch1] < -25 || vexRT[Ch2] < -25) {
			writeDebugStreamLine("Degree: %i", deg(vexRT[Ch1], vexRT[Ch2]));
			int pythag = (vexRT[Ch1] * vexRT[Ch1]) + (vexRT[Ch2] * vexRT[Ch2]);
			int str = (int)sqrt(pythag);
			writeDebugStreamLine("Strength: %i", str);
			wait10Msec(10);
		}
	}
}
