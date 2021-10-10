//--------------------------------------------------------------------
// For use with a 573 SDVX Controller
//
// This sketch maps 2 rotary encoders and uses 7 digital 
// inputs. (7 for its keys)
//
// All digital pins are grounded when they are pressed.
//
// NOTE: This sketch file is for use with Arduino Leonardo or Micro 
// only.
//
// by lyzzz
// 2021-10-10
//--------------------------------------------------------------------

#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  10, 0,                  // Button Count, Hat Switch Count
  true, true, false,      // X, Y and Z Axis
  false, false, false,    // No Rx, Ry, or Rz
  false, false,           // No rudder or throttle
  false, false, false);   // No accelerator, brake, or steering

void setup() {
  // Initialize Pins
  // FX and Start Buttons
  pinMode(7, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  // VOL-L Rotary Encoder
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  // VOL-R Rotary Encoder
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
    
  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-360, 360);
  Joystick.setYAxisRange(-360, 360);
}

// Last state of the buttons
int keys[7] = {10, 8, 4, 6, 9, 12, 7};
int lastButtonState[7] = {0,0,0,0,0,0,0};
Encoder volL(1,0);
Encoder volR(2,3);

void loop() {
  // Read pin values
  for (int index = 0; index < 7; index++) {
    int currentButtonState = !digitalRead(keys[index]);
    if (currentButtonState != lastButtonState[index]) {
      switch (index) {
        // BT-A
        case 0:
          Joystick.setButton(1, currentButtonState);
          break;
          
        // BT-B
        case 1:
          Joystick.setButton(2, currentButtonState);
          break;
          
        // BT-C
        case 2:
          Joystick.setButton(3, currentButtonState);
          break;
          
        // BT-D
        case 3:
          Joystick.setButton(4, currentButtonState);
          break;
          
        // FX-L
        case 4:
          Joystick.setButton(5, currentButtonState);
          break;
          
        // FX-R
        case 5:
          Joystick.setButton(6, currentButtonState);
          break;
          
        // Start
        case 6:
          Joystick.setButton(0, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  if (volL.read() >= 360) {
    volL.write(-360);
  }
  else if (volL.read() <= -360) {
    volL.write(360);
  }

  if (volR.read() >= 360) {
    volR.write(-360);
  }
  else if (volR.read() <= -360) {
    volR.write(360);
  }

  Joystick.setXAxis(volL.read());
  Joystick.setYAxis(volR.read());
 }
