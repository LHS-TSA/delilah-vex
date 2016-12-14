// SECTION: Drive Motor Control

// Global Variables
short botVelocityX = 0;
short botVelocityY = 0;
short botVelocityZ = 0;             // Rotation
short motorSpeeds[4] = {0, 0, 0, 0};
// bool motorZero[4] = {false, false, false, false};

short botAngle = 0;
short botSpeed = 0;
short botRotation = 0;              // rotation of the robot

int deg_sq = 0;
int deg_cu = 0;
float deg_sqf = 0;
float deg_cuf = 0;
float deg_f = 0;
float nfm = 0;

short mtr_localGetNonFacingMotorSpeed(int degree) {
  // TODO: OPTIMIZE ME!
  // actual function: 0.00031 * deg^3 + -0.041828 * deg^2 + 4.05596*deg + -126.037
  deg_sq = degree * degree;
  deg_cu = deg_sq * degree;

  deg_sqf = -0.041828 * deg_sq;
  deg_cuf = 0.00031 * deg_cu;
  deg_f = 4.05596 * degree;

  return (short)(deg_sqf + deg_cuf + deg_f + -126.037);
}

short mtr_localGetCurrentQuad() {
  // TODO: Make these more specific
  if (botVelocityY >= 0) {
    return (botVelocityX > 0 ? 1 : 2);
  } else {
    return (botVelocityX > 0 ? 4 : 3);
  }
}

void mtr_localQuad1() {
  nfm = mtr_localGetNonFacingMotorSpeed(botAngle);

  motorSpeeds[0] = (nfm * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (-MAX_MOTOR_B * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (-nfm * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (MAX_MOTOR_D * botSpeed) / MAX_MOTOR_D;
}

void mtr_localQuad2() {
  nfm = mtr_localGetNonFacingMotorSpeed(botAngle - 90);

  motorSpeeds[0] = (MAX_MOTOR_A * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (nfm * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (-MAX_MOTOR_C * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (-nfm * botSpeed) / MAX_MOTOR_D;
}

void mtr_localQuad3() {
  nfm = -mtr_localGetNonFacingMotorSpeed(-botAngle - 90);

  motorSpeeds[0] = (-nfm * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (MAX_MOTOR_B * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (nfm * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (-MAX_MOTOR_D * botSpeed) / MAX_MOTOR_D;
}

void mtr_localQuad4() {
  nfm = -mtr_localGetNonFacingMotorSpeed(-botAngle);

  motorSpeeds[0] = (-MAX_MOTOR_A * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (-nfm * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (MAX_MOTOR_C * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (nfm * botSpeed) / MAX_MOTOR_D;
}



void mtr_localCalcVelocity() {
  botAngle = (short)(atan2(botVelocityY, botVelocityX) * 57.2958);
  botSpeed = sqrt(botVelocityX * botVelocityX + botVelocityY * botVelocityY);
}

void mtr_localRotation() {
  motorSpeeds[0] = botVelocityZ;
  motorSpeeds[1] = botVelocityZ;
  motorSpeeds[2] = botVelocityZ;
  motorSpeeds[3] = botVelocityZ;
}

void mtr_localMotorSpeed() {
  if (!auton) { mtr_localCalcVelocity(); }

  switch (mtr_localGetCurrentQuad()) {
    case 4: mtr_localQuad4(); break;
    case 3: mtr_localQuad3(); break;
    case 2: mtr_localQuad2(); break;
    default: mtr_localQuad1();
  }
}

void mtr_doMotorTick() {
  if (botVelocityZ != 0) {
    mtr_localRotation();
  } else {
    mtr_localMotorSpeed();
  }
}

void mtr_commitMotorSpeeds() {
  if (slowMode) {
    MOTOR_A = (motorSpeeds[0] * SLOW_MAX_SPEED) / 127;
    MOTOR_B = (motorSpeeds[1] * SLOW_MAX_SPEED) / 127;
    MOTOR_C = (motorSpeeds[2] * SLOW_MAX_SPEED) / 127;
    MOTOR_D = (motorSpeeds[3] * SLOW_MAX_SPEED) / 127;
  } else {
    MOTOR_A = motorSpeeds[0];
    MOTOR_B = motorSpeeds[1];
    MOTOR_C = motorSpeeds[2];
    MOTOR_D = motorSpeeds[3];
  }
}
