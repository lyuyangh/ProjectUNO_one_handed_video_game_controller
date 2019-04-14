#include "Keyboard.h"
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

void setup() {
  pinMode(SW_pin, INPUT);asa
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
  Keyboard.begin();
}

void loop() {
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

  if(Joystick_X == 0 ){
    Keyboard.write('a');
  }
  if(Joystick_X == 1023 ){
    Keyboard.write('d');
  }
  if(Joystick_Y == 0){
    Keyboard.write('s');
  }
  if(Joystick_Y == 1023){
    Keyboard.write('w');
  }
  
  delay(500);
}
