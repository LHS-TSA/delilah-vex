#ifndef DELILAH_MOTORS_H
#define DELILAH_MOTORS_H

extern short botVelocityX;
extern short botVelocityY;
extern short botVelocityZ;

void mtr_doMotorTick();
void mtr_commitMotorSpeeds();

#endif // DELILAH_MOTORS_H
