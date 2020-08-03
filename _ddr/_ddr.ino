//--------------------------------------------------------------------
// For use with a 573 DDR Controller
//
// This sketch uses 16 digital inputs and maps them to 4 keys.
//
// All digital pins are grounded when they are pressed.
// Required libraries: 
// https://github.com/MHeironimus/ArduinoJoystickLibrary
// 
// NOTE: This sketch file is for use with Arduino Leonardo or Micro 
// only.
//
// by limyz
// 2020-07-18
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  4, 0,                   // Button Count, Hat Switch Count
  false, false, false,    // X, Y and Z Axis
  false, false, false,    // No Rx, Ry, or Rz
  false, false,           // No rudder or throttle
  false, false, false);   // No accelerator, brake, or steering

void setup() {
  // Initialize Pins
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  
  // Initialize Joystick Library
  Joystick.begin();
}

byte keys[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, A0, A1};
int lastButtonState[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void loop() {  
  // Read pin values
  for (int index = 0; index < 16; index++) {
    int currentButtonState = !digitalRead(keys[index]);
    if (currentButtonState != lastButtonState[index]) {
      if (index == 0 | index == 1 | index == 2 | index == 3) {
          Joystick.setButton(0, currentButtonState);
      }
      if (index == 4 | index == 5 | index == 6 | index == 7) {
          Joystick.setButton(1, currentButtonState);
      }
      if (index == 8 | index == 9 | index == 10 | index == 11) {
          Joystick.setButton(2, currentButtonState);
      }
      if (index == 12 | index == 13 | index == 14 | index == 15) {
          Joystick.setButton(3, currentButtonState);
          digitalWrite(A3, HIGH);
      }
      lastButtonState[index] = currentButtonState;
    }
  }
}
