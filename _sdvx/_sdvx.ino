//--------------------------------------------------------------------
// For use with a 573 SDVX Controller
//
// This sketch maps 2 rotary encoders and uses 14 digital 
// inputs. (7 for the keys and 7 for its LEDs)
//
// All digital pins are grounded when they are pressed.
//
// NOTE: This sketch file is for use with Arduino Leonardo or Micro 
// only.
//
// by lyzzz
// 2020-04-26
//--------------------------------------------------------------------

#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  10, 0,                   // Button Count, Hat Switch Count
  true, true, false,      // X, Y and Z Axis
  false, false, false,    // No Rx, Ry, or Rz
  false, false,           // No rudder or throttle
  false, false, false);   // No accelerator, brake, or steering

void setup() {
  // Initialize Pins
  // FX and Start Buttons
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  
  // FX and Start LEDs
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);

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

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 4;

// Last state of the buttons
byte keys[] = {4, 5, 6, 7, 8, 9, 10};
byte LEDs[] = {A3, A2, A1, A0, 15, 14, 16};
int lastButtonState[7] = {0,0,0,0,0,0,0};
Encoder volL(0,1);
Encoder volR(2,3);
long previousMicros = 0;
long interval = 100000; // interval at which to blink (microseconds)

void loop() {
  unsigned long currentMicros = micros();
  
  // Read pin values
  for (int index = 0; index < 7; index++) {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index]) {
      switch (index) {
        // Start
        case 0:
          Joystick.setButton(0, currentButtonState);
          digitalWrite(A3, HIGH);
          break;
        // BT-A
        case 1:
          Joystick.setButton(1, currentButtonState);
          digitalWrite(A2, HIGH);
          break;
        // BT-B
        case 2:
          Joystick.setButton(2, currentButtonState);
          digitalWrite(A1, HIGH);
          break;
        // BT-C
        case 3:
          Joystick.setButton(3, currentButtonState);
          digitalWrite(A0, HIGH);
          break;
        // BT-D
        case 4:
          Joystick.setButton(4, currentButtonState);
          digitalWrite(15, HIGH);
          break;
        // FX-L
        case 5:
          Joystick.setButton(5, currentButtonState);
          digitalWrite(14, HIGH);
          break;
        // FX-R
        case 6:
          Joystick.setButton(6, currentButtonState);
          digitalWrite(16, HIGH);
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

  if(currentMicros - previousMicros > interval) { 
    previousMicros = currentMicros;
 
    // set the LED with the ledState of the variable:
    for(int index = 0; index < 7; index++) {
      digitalWrite(LEDs[index], LOW);
    }
  }
 }
