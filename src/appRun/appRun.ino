/*
 * appRun.ino
 * Created: 4/15/19
 * Last Modified: 4/15/19
 * 
 * Change Log:
 *    0.1 - basic structure
 *    0.2 - add Gyro_controller class
 * Known Issues:
 *    1. need init exception handling
 */
#include "Gyro_controller.h"

const int responseDelay = 30;

Gyro_controller view_control;
//ScrollWheel_controller item_select;
//Joystick_controller movement_control;

void setup() {
  
}

void loop() {
  view_control.changeView();
  //item_select.select();
  //movement_control.makeMovement();
  //checkButtons();
  delay(responseDelay);

}
