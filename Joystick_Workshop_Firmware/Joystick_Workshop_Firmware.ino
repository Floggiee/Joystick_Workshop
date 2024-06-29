#include <Arduino.h>
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 3, 0,
  true, true, true, false, false, false,
  false, false, false, false, false);


// specify input pins
const int xPin = A1;
const int yPin = A0;
const int thrPin = A2;

const int stickButton = 15;
const int rudL = 8;
const int rudR = 9;

//specify hardware specific values
int yCenter = 501;
int yFullForward = 0;
int yFullBackward = 1023;
int yDeadzone = 2;

int xCenter = 488;
int xFullLeft = 0;
int xFullRight = 1023;
int xDeadzone = 2;

//specify map range
int range = 512;




void setup() {
  
  Serial.begin(9600);

  pinMode(stickButton, INPUT_PULLUP);
  pinMode(rudL, INPUT_PULLUP);
  pinMode(rudR, INPUT_PULLUP);

  Joystick.begin();

  Joystick.setXAxisRange(-512, 512);
  Joystick.setYAxisRange(-512, 512);
  Joystick.setZAxisRange(0, 1023);


}

void loop() {


  x();
  y();
  thr();

  Joystick.setButton(0, !digitalRead(rudL));
  Joystick.setButton(1, !digitalRead(rudR));
  Joystick.setButton(2, !digitalRead(stickButton));


  delay(10);

}

int center(int rawValue, int center, int deadzone) {
  if ((rawValue > center - deadzone) && (rawValue < center + deadzone)) {
    return 0;
  } else {
    int output = rawValue - center;
    return output;
  }
}

int mapCenteredValue(int centeredValue, int minCenteredEndstop, int maxCenteredEndstop, int range) {
  if(centeredValue > 0) {
    int mappedPositive = map(centeredValue, 0, maxCenteredEndstop, 0, range);
    return mappedPositive;
  } else if(centeredValue < 0) {
    int mappedNegative = map(centeredValue, 0, minCenteredEndstop, 0, -1*range);
    return mappedNegative;
  } else {
    return 0;
  }
} 

void y() {
  int yValue = analogRead(yPin);

  int yCentered = center(yValue, yCenter, yDeadzone);
  

  Joystick.setYAxis(yCentered);
}


void x() {
  int xValue = analogRead(xPin);

  int xCentered = center(xValue, xCenter, xDeadzone);
  

  Joystick.setXAxis(xCentered);
}

void thr() {
  int thrValue = analogRead(thrPin);

  Joystick.setZAxis(thrValue);
}

