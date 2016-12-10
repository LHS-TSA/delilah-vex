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

short mtr_localGetNonFacingMotorSpeed(int degree) {
  // TODO: OPTIMIZE ME!
  // actual function: 0.00031 * deg^3 + -0.041828 * deg^2 + 4.05596*deg + -126.037
  int deg_sq = degree * degree;
  int deg_cu = deg_sq * degree;

  float deg_sqf = -0.041828 * deg_sq;
  float deg_cuf = 0.00031 * deg_cu;
  float deg_f = 4.05596 * degree;

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
  float nfm = mtr_localGetNonFacingMotorSpeed(botAngle);

  motorSpeeds[0] = (nfm * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (-MAX_MOTOR_B * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (-nfm * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (MAX_MOTOR_D * botSpeed) / MAX_MOTOR_D;
}

void mtr_localQuad2() {
  float nfm = mtr_localGetNonFacingMotorSpeed(botAngle - 90);

  motorSpeeds[0] = (MAX_MOTOR_A * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (nfm * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (-MAX_MOTOR_C * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (-nfm * botSpeed) / MAX_MOTOR_D;
}

void mtr_localQuad3() {
  float nfm = -mtr_localGetNonFacingMotorSpeed(-botAngle - 90);

  motorSpeeds[0] = (-nfm * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (MAX_MOTOR_B * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (nfm * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (-MAX_MOTOR_D * botSpeed) / MAX_MOTOR_D;
}

void mtr_localQuad4() {
  float nfm = -mtr_localGetNonFacingMotorSpeed(-botAngle);

  motorSpeeds[0] = (-MAX_MOTOR_A * botSpeed) / MAX_MOTOR_A;
  motorSpeeds[1] = (-nfm * botSpeed) / MAX_MOTOR_B;
  motorSpeeds[2] = (MAX_MOTOR_C * botSpeed) / MAX_MOTOR_C;
  motorSpeeds[3] = (nfm * botSpeed) / MAX_MOTOR_D;
}



void mtr_localCalcVelocity() {
  botAngle = (short)(atan2(botVelocityY, botVelocityX) * 57.2958);
  botSpeed = sqrt(botVelocityX * botVelocityX + botVelocityY * botVelocityY);
}

/* This won't work proportionally
 * void mtr_localZeroMotors() {
 *   for (int i=0; i<4; i++) {
 *     if (!motorZero[i]) {
 *       if (motorSpeeds[i] > 0) {
 *         motorSpeeds[i]--;
 *       } else if (motorSpeeds[i] < 0) {
 *         motorSpeeds[i]++;
 *       } else if (motorSpeeds[i] == 0) {
 *         motorZero[i] = false;
 *       }
 *     }
 *   }
 * }
 */

 void mtr_localRotation() {
   motorSpeeds[0] = botVelocityZ;
   motorSpeeds[1] = botVelocityZ;
   motorSpeeds[2] = botVelocityZ;
   motorSpeeds[3] = botVelocityZ;
 }

 void mtr_localMotorSpeed() {
   if (botVelocityZ > 0) {
     mtr_localRotation();
   } else {
     if (!auton) { mtr_localCalcVelocity(); }

     switch (mtr_localGetCurrentQuad()) {
       case 4: mtr_localQuad4(); break;
       case 3: mtr_localQuad3(); break;
       case 2: mtr_localQuad2(); break;
       default: mtr_localQuad1();
     }
   }
 }

void mtr_doMotorTick() {
  // mtr_localZeroMotors();
  mtr_localMotorSpeed();
  // TODO: Motor Tick
}

void mtr_commitMotorSpeeds() {
  if (slowMode) {
    MOTOR_A = motorSpeeds[0] / SLOW_MAX_SPEED;
    MOTOR_B = motorSpeeds[1] / SLOW_MAX_SPEED;
    MOTOR_C = motorSpeeds[2] / SLOW_MAX_SPEED;
    MOTOR_D = motorSpeeds[3] / SLOW_MAX_SPEED;
  } else {
    MOTOR_A = motorSpeeds[0];
    MOTOR_B = motorSpeeds[1];
    MOTOR_C = motorSpeeds[2];
    MOTOR_D = motorSpeeds[3];
  }
}
