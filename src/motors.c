// SECTION: Drive Motor Control

// Global Variables
short rotation = 0;             // rotation of the robot
bool slowMode = false;          // Reduces speed by indicated percent
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
  // TODO; motor zeroing
}

void mtr_doMotorTick() {
  // TODO: Motor Tick
}
