/*
 * Gyro_controller.h
 * Created: 4/15/19
 * Last Modified: 4/15/19
 * Author: Steven Hu
 * 
 * Known Issues:
 *    1. need function to do initial calibration
 *    2. need function to change sensitivity
 *    3. need function to adjust tolerance (not used for ver 0.2.5
 * Circuit:
 *    Arduino Leonardo
 *    GY521 -MPU6050 Gyro+Acc
 *      D3 <-> SCL 
 *      D2 <-> SDA
 *      D0 <-> INT
 */
#ifndef GYRO_CONTROLLER_H
#define GYRO_CONTROLLER_H

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

class Gyro_controller
{
private:
  int16_t ax,ay,az,gx,gy,gz;
  int mouse_x,mouse_y;
  int responseDelay;
  int sensitivity_x = 140;
  int sensitivity_y = 140;
  int mouse_y_bias = 350;
  MPU6050 mpu;
public:
  Gyro_controller();
  int calibrate();
  void changeView();
};

#endif  /* GYRO_CONTROLLER_H*/
