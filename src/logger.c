// SECTION: Logger

/**
 * Logs the state of the motors.
 * Writes to the Debug Stream in a comma-seperated formatted list
 */
void logState() {
  if (loopCount == 0) {   // Prints the dubug header on first output
    writeDebugStreamLine("loopCount,leftMotor,rightMotor,sideMotor,highHang,slowMode,isFlipped");
  }

  writeDebugStream("%i", loopCount);
  writeDebugStream(",%i",motor[leftMaster]);
  writeDebugStream(",%i", motor[rightMaster]);
  writeDebugStream(",%i",motor[sideMotor]);
  writeDebugStream(",%i",motor[armLeft]);
  writeDebugStream(",%d",slowMode);
  writeDebugStreamLine(",%d",isFlipped);

  loopCount++;
}
