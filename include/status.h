#ifndef DELILAH_STATUS_H
#define DELILAH_STATUS_H

void stat_flashLeds(int amt);
void stat_flashLedRed(int amt);
void stat_flashLedYellow(int amt);
void stat_flashLedGreen(int amt);
void stat_doLedPretest();
void stat_ledController(void* args);

#endif // DELILAH_STATUS_H
