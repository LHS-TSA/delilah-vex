# Documentation #
**Generated [here](https://delight-im.github.io/Javadoc-to-Markdown/) on 10/23/2016 10:02PM EST**

### `void mvtForwardLeft(signed char speed)` ###
  **Left motors movement control.**  
  Sets the value of the left motors in normal mode or right motors in flipped mode; Speed is divided by slowModePercent if in slow mode
  * **Parameters:** `speed` — Speed in range -127 to 127

### `void mvtForwardRight(signed char speed)` ###
  **Right motors movement control.**  
  Sets the value of the right motors in normal mode or left motors in flipped mode; Speed is divided by slowModePercent if in slow mode
  * **Parameters:** `speed` — Speed in range -127 to 127

### `void mvtSide(signed char speed)` ###
  **Left motors movement control.**  
  Sets the value of the side motors in normal mode; Value is negated in flipped mode; Speed is divided by slowModePercentSide if in slow mode
  * **Parameters:** `speed` — Speed in range -127 to 127

### `void mvtHighHang(signed char speed)` ###
  **High hang motors movement control.**  
  Sets the value of the high hang motors in normal mode; Value is not effected by flipped mode or slow mode
  * **Parameters:** `speed` — Speed in range -127 to 127

### `void ctlFlipSides()` ###
  **Controls when front side of robot is swapped.**  
  Tests for presses to Btn8D and flips the bool value isFlipped when activated; The red led will be active when in flipped mode

### `void ctlSlowMode()` ###
  **Controls when motors are at reduced speed.**  
  Tests for presses to Btn8R and flips the bool value slowMode when activated; The green led will be active when in slow mode

### `void ctlJoysticks()` ###
  **Controls the speed of the left and right motors.**  
  Tests Ch3 for right motors and Ch2 for left motors; Does not activate movement without joystick being over jsThreshold to prevent ghost movement

### `void ctlSideMovement()` ###
  **Controls the speed of the side motor.**  
  Tests Btn6D and Bth5D for activation and sets speed to highest level for the duration of their activation

### `void ctlHighHang()` ###
  **Controls the speed of the high hang motors.**  
  Tests Btn7U and Btn7D for activation and sets speed to highest level for the duration of their activation

### `void logState()` ###
  **Logs the state of the motors.**  
  Writes to the Debug Stream in a comma-seperated formatted list

### `void pre_auton()` ###
  **Pre-Autonomous Functions.**  
  Includes all activities that occur before the competition starts; Turns the leds off and sets up the slave motors.

### `task autonomous()` ###
  **Autonomous Task.**

### `task usercontrol()` ###
  **User Control Task.**
