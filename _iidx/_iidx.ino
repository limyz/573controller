//--------------------------------------------------------------------
// For use with a 573 IIDX Controller (1P)
//
// This sketch maps 2 photoelectric sensors and uses 16 digital 
// inputs. (9 for the keys and 7 for its LEDs)
//
// All digital pins are grounded when they are pressed.
// Required libraries: 
// https://github.com/MHeironimus/ArduinoJoystickLibrary
// https://github.com/PaulStoffregen/Encoder
//
// NOTE: This sketch file is for use with Arduino Leonardo or Micro 
// only.
//
// by limyz
// 2020-04-24
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
  // P1 - 7 Key Buttons
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  
  // P1 - 7 Key LEDs
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  // P1 - Effect and VEFX Buttons
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  
  // P1 - Effect and VEFX LEDs
  // Unused

  // P1 - Turntable Photoelectric Sensor
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
    
  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-360, 360);
  Joystick.setYAxisRange(-360, 360);
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 2;

// Last state of the buttons
byte keys[] = {2, 3, 4, 5, 6, 7, 8};
byte LEDs[] = {A3, A2, 14, 15, 16, A0, A1};
int lastButtonState[9] = {0,0,0,0,0,0,0,0,0};
Encoder turnTable(0,1);
long previousMicros = 0;
long interval = 100000; // interval at which to blink (microseconds)

void loop() {
  unsigned long currentMicros = micros();
  
  // Read pin values
  for (int index = 0; index < 9; index++) {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index]) {
      switch (index) {
        case 0:
          Joystick.setButton(0, currentButtonState);
          digitalWrite(A2, HIGH);
          break;
        case 1:
          Joystick.setButton(1, currentButtonState);
          digitalWrite(A3, HIGH);
          break;
        case 2:
          Joystick.setButton(2, currentButtonState);
          digitalWrite(14, HIGH);
          break;
        case 3:
          Joystick.setButton(3, currentButtonState);
          digitalWrite(15, HIGH);
          break; 
        case 4:
          Joystick.setButton(4, currentButtonState);
          digitalWrite(16, HIGH);
          break;
        case 5:
          Joystick.setButton(5, currentButtonState);
          digitalWrite(A0, HIGH);
          break;
        case 6:
          Joystick.setButton(6, currentButtonState);
          digitalWrite(A1, HIGH);
          break;
        case 7:
          Joystick.setButton(8, currentButtonState);
          break;
        case 8:
          Joystick.setButton(9, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }
  
  if (turnTable.read() >= 360 ) {
    turnTable.write(-360);
  }
  else if (turnTable.read() <= -360) {
    turnTable.write(360);
  }
  
  Joystick.setXAxis(turnTable.read());

  if(currentMicros - previousMicros > interval) {
    previousMicros = currentMicros;

    for(int index = 0; index < 9; index++) {
      digitalWrite(LEDs[index], LOW);
    }
  }
 }
