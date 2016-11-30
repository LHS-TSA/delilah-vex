// SECTION: Drive Motor Control

// Global Variables
short botVelocity[3] = {0 ,0, 0};
short motorSpeeds[4] = {0, 0, 0, 0};
bool motorZero[4] = {false, false, false, false};

void mtr_localMotorSpeed(short speedA,
                         short speedB,
                         short speedC,
                         short speedD) {
  // TODO: motor speeds
}

void mtr_localZeroMotors() {
  for (int i=0; i<4; i++) {
    if (!motorZero[i]) {
      if (motorSpeeds[i] > 0) {
        motorSpeeds[i]--;
      } else if (motorSpeeds[i] < 0) {
        motorSpeeds[i]++;
      } else if (motorSpeeds[i] == 0) {
        motorZero[i] = false;
      }
    }
  }
}

void mtr_doMotorTick() {
  mtr_localZeroMotors();
  mtr_localMotorSpeed(motorSpeeds[0], motorSpeeds[1], motorSpeeds[2], motorSpeeds[3]);
  // TODO: Motor Tick
}
