#include <Arduino.h>
#include <Joystick.h>
Joystick_ Joystick;


// specify input pins
const int xPin = A1;
const int yPin = A0;
const int thrPin = A2;

const int stickButton = 15;
const int rudL = 8;
const int rudR = 9;

// setup variables for analog values
int xValue;
int yValue;
int thrValue;






void setup() {
  
  Serial.begin(9600);

  pinMode(stickButton, INPUT_PULLUP);
  pinMode(rudL, INPUT_PULLUP);
  pinMode(rudR, INPUT_PULLUP);

}

void loop() {

  Joystick.sendState();
  delay(10);

  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  thrValue = analogRead(thrPin);

  Serial.print("X ");
  Serial.print(xValue);
  Serial.println();

  Serial.print("Y ");
  Serial.print(yValue);
  Serial.println();

  Serial.print("thr ");
  Serial.print(thrValue);
  Serial.println();

  Serial.print("Y ");
  Serial.print(digitalRead(rudL));
  Serial.println();

  Serial.print("Y ");
  Serial.print(digitalRead(rudR));
  Serial.println();

}

