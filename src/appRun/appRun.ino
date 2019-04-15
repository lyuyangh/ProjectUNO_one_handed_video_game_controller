/*
  appRun.ino
  Created: 4/13/19
  Last Modified: 4/14/19

  Change Log:
     0.1 - basic structure
     0.2 - add Gyro_controller class
  Known Issues:
     1. need init exception handling
*/
#include "Keyboard.h"
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>
//#include "PinChangeInt.h"

////////////
const int buttonLeft = A0;          // input pin for pushbutton
const int buttonRight = A1;
const int buttonDLeft = A2;          // input pin for pushbutton
const int buttonDRight = A3;

/////////////////////////////
//Rotorary Encoder
const int pinA = 7; // Our first hardware interrupt pin is digital pin 2
//static int pinB = 8; // Our second hardware interrupt pin is digital pin 3
int oldA = 0;
int newA;
int count = 0;
//////////////////////////

const int SW_pin = 1; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

const int responseDelay = 40;

int16_t ax, ay, az, gx, gy, gz;
int mouse_x, mouse_y;
int sensitivity_x = 140;
int sensitivity_y = 240;
int mouse_y_bias = 350;
MPU6050 mpu;

void init_encoder()
{
  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  //pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  //attachPinChangeInterrupt(digitalPinToInterrupt(pinA), PinA, RISING);
  //attachPinChangeInterrupt(digitalPinToInterrupt(pinB), PinB, RISING);

  //attachInterrupt(4,newPinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  //attachInterrupt(digitalPinToInterrupt(pinB),PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
}
void init_joystick()
{
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  //Serial.begin(115200);
  Keyboard.begin();
}
void init_gyro_controller()
{
  Serial.println("<<<<Gyro init>>>>");

  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
  }
  Mouse.begin();
  Serial.println("<<<<Gyro has been initialized>>>>");
  // should prompt to option to calibrate, change sensitivity
}

void scroll_move()
{
  newA = digitalRead(pinA);
  if (newA != oldA) {
    count++;
    oldA = newA;
  }
  if (count > 2) {
    Mouse.move(0, 0, 6);
    count = 0;
    Serial.println("count to 0");
  }
}

void joystick_makeMovement()
{
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");

  //if x ==0 = left, x==1023 = right
  //if y ==0  down, y ==1023 = up

  //get values from Joystick X
  int Joystick_X = analogRead(X_pin);
  int Joystick_Y = analogRead(Y_pin);

  if (Joystick_X == 0 ) {
    Keyboard.write('a');
  }
  if (Joystick_X == 1023 ) {
    Keyboard.write('d');
  }
  if (Joystick_Y == 0) {
    Keyboard.write('s');
  }
  if (Joystick_Y == 1023) {
    Keyboard.write('w');
  }
}

void gyro_changeView()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  mouse_x = (gz) / sensitivity_x;   //gz+15
  mouse_y = -(gy - mouse_y_bias) / sensitivity_y;  //gy-100

  Serial.print("gz = ");
  Serial.print(gz);
  Serial.print(" | gy = ");
  Serial.print(gy);

  Serial.print("\nX = ");
  Serial.print(mouse_x);
  Serial.print(" | Y = ");
  Serial.println(mouse_y);

  Mouse.move(mouse_x, mouse_y, 0);
}

//ScrollWheel_controller item_select;
//Joystick_controller movement_control;
/*
  void check_button()
  {
  int buttonStateLeft = digitalRead(buttonLeft);
  if (buttonStateLeft == HIGH) //if the button is pressed
  {
    // type out a message
    Mouse.click(MOUSE_LEFT);
    delay(50); //Delay for bounce & to let you computer catch up
  }
  // read the pushbutton:
  int buttonStateRight = digitalRead(buttonRight);
  if (buttonStateRight == HIGH) //if the button is pressed
  {
    // type out a message
    Mouse.click(MOUSE_RIGHT);
    delay(50); //Delay for bounce & to let you computer catch up
  }

  int buttonStateLeft = digitalRead(buttonDLeft);
  if (buttonStateLeft == HIGH) //if the button is pressed
  {
    // type out a message
    Keyboard.print(KEY_LEFT_SHIFT);
    delay(50); //Delay for bounce & to let you computer catch up
  }
  // read the pushbutton:
  int buttonStateRight = digitalRead(buttonDRight);
  if (buttonStateRight == HIGH) //if the button is pressed
  {
    // type out a message
    Keyboard.click(‘space’);
    delay(50); //Delay for bounce & to let you computer catch up
  }
  }
*/
void setup() {
  Serial.begin(9600);
  Serial.println("here");

  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonDLeft, INPUT);
  pinMode(buttonDRight, INPUT);

  init_gyro_controller();
  init_joystick();
  init_encoder();
}

void loop() {

  //Serial.println("12
  //checkButtons();
  gyro_changeView();
  joystick_makeMovement();
  scroll_move();
  Serial.print("count: ");
  Serial.println(count);
  //  check_button();
  delay(responseDelay);
}
