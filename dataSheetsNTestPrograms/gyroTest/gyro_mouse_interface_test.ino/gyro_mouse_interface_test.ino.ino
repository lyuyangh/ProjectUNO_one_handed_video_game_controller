/*
 * gyro_mouse_interface_test.ino
 * Created: 4/14/19
 * Last Modified: 4/14/19
 * 
 * Change Log:
 *    0.1 - Adapted from Accelerometer Mouse by MrHobbyelectronics
 *    0.2 - add Mouse.begin();
 *    0.2.5 - caliberate mouse_y_bias on one computer
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
 
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int mouse_x, mouse_y;
const int responseDelay = 70;
const int sensitivity_x = 140;
const int sensitivity_y = 140;
const int mouse_y_bias = 350;
//const int tolerance = 20;
//int button1 = 6;
//int button2 = 7;
//int buttonState1 = 0; 
//int buttonState2 = 0; 

void setup() {

  Serial.begin(9600);
  Wire.begin();
  //pinMode(button1, INPUT);
  //pinMode(button2, INPUT);
  mpu.initialize();
  if (!mpu.testConnection()) { while (1); }
  Mouse.begin();
}

void loop() {
  // get all data from acceleerometer and gyro
  // use gyro x,y axis movement to calculate mouse movement
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  mouse_x = -(gz)/sensitivity_x;     //gz+15
  mouse_y = (gy- mouse_y_bias)/sensitivity_y;     //gy-100

  Serial.print("gz = ");
  Serial.print(gz);
  Serial.print(" | gy = ");
  Serial.print(gy);
  
  Serial.print("\nX = ");
  Serial.print(mouse_x);
  Serial.print(" | Y = ");
  Serial.println(mouse_y);
  
  Mouse.move(mouse_x, mouse_y,0);
  /*
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  
 if (buttonState1 == HIGH) {
    Mouse.press(MOUSE_LEFT);
    delay(100);
    Mouse.release(MOUSE_LEFT);
    delay(200);
  
  } 
  else if(buttonState2 == HIGH) {
    Mouse.press(MOUSE_RIGHT);
    delay(100);
    Mouse.release(MOUSE_RIGHT);
    delay(200);
  }
  */
  delay(responseDelay);
}

