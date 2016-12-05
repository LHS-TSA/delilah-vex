// SECTION: Drive Motor Control

// Global Variables
short botVelocity[3] = {0 ,0, 0};  // X,Y,Z
short motorSpeeds[4] = {0, 0, 0, 0};
bool motorZero[4] = {false, false, false, false};

short botAngle = 0;
short botSpeed = 0;

short botRotation = 0;              // rotation of the robot
bool slowMode = false;              // Reduces speed by indicated percent

void mtr_localMotorSpeed() {
  mtr_localCalcVelocity();

  switch (mtr_localGetCurrentQuad) {
    case 4: mtr_localQuad4(); break;
    case 3: mtr_localQuad3(); break;
    case 2: mtr_localQuad2(); break;
    case default: mtr_localQuad1();
  }

  MOTOR_A = motorSpeeds[0];
  MOTOR_B = motorSpeeds[1];
  MOTOR_C = motorSpeeds[2];
  MOTOR_D = motorSpeeds[3];
}

short mtr_localGetCurrentQuad() {
  if (botVelocity[1] >= 0) {
    return (botVelocity[0] > 0 ? 1 : 2);
  } else {
    return (botVelocity[0] > 0 ? 4 : 3);
  }
}

void mtr_localQuad1() {

}

void mtr_localQuad2() {

}

void mtr_localQuad3() {

}

void mtr_localQuad4() {

}

short mtr_localGetNonFacingMotorSpeed(int degree) {
  // TODO: OPTIMIZE ME!
  // actual function: 0.00031 * deg^3 + -0.041828 * deg^2 + 4.05596*deg + -126.037
  int deg_sq = degree * degree;
  int deg_cu = deg_sq * degree;

  float deg_sqf *= -0.041828;
  float deg_cuf *= 0.00031;
  float deg_f *= 4.05596;

  return (short)(deg_sqf + deg_cuf + deg_f + -126.037);
}

void mtr_localCalcVelocity() {
  botAngle = (short)(atan2(botVelocity[0], botVelocity[1]) * 57.2958); // I think this is reversed
  botSpeed = sqrt(botVelocity[0] * botVelocity[0] + botVelocity[1] * botVelocity[1]);
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
  mtr_localMotorSpeed();
  // TODO: Motor Tick
}
