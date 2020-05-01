//--------------------------------------------------------------------
// For use with a 573 or GH Guitar Controller
//
// This sketch maps a ADXL345 accelerometer via I2C and uses 7 digital 
// inputs - 5 buttons and a 2 hat switches for the pick.
//
// All digital pins are grounded when they are pressed.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Micro only.
//
// by lyzzz
// 2019-07-25
//--------------------------------------------------------------------

#include <Joystick.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(573);

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  5, 1,                  // Button Count, Hat Switch Count
  true, true, true,      // X, Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  // Pins 2 and 3 are reserved for I2C
  //pinMode(2, INPUT_PULLUP);
  //pinMode(3, INPUT_PULLUP);

  // Pins 5 to 9 -> R, G, B, Y, P
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  // Pins 9 to 10 -> Guitar Pick
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  // Initialise ADXL345
  accel.begin();

  // Set Range for ADXL345
  accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  // accel.setRange(ADXL345_RANGE_2_G);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-100, 100);
  Joystick.setYAxisRange(-100, 100);
  Joystick.setZAxisRange(-100, 100);
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 4;
const int pinToHatSwitchMap = 9;

// Last state of the buttons
int lastButtonState[5] = {0,0,0,0,0};
int lastHatSwitchState[2] = {0,0};

void loop() {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);

  bool valueChanged = false;
  
  Joystick.setXAxis(event.acceleration.x);
  Joystick.setYAxis(event.acceleration.y);
  Joystick.setZAxis(event.acceleration.z);

  // Read pin values
  for (int index = 0; index < 5; index++) {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index]) {
      switch (index) {
        case 0:
          Joystick.setButton(0, currentButtonState);
          break;
        case 1:
          Joystick.setButton(1, currentButtonState);
          break;
        case 2:
          Joystick.setButton(2, currentButtonState);
          break;
        case 3:
          Joystick.setButton(3, currentButtonState);
          break; 
        case 4:
          Joystick.setButton(4, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  for (int index = 0; index < 2; index++) {
    int currentHatSwitchState = digitalRead(index + pinToHatSwitchMap);
    if (currentHatSwitchState != lastHatSwitchState[index]) {
      valueChanged = true;
      lastHatSwitchState[index] = currentHatSwitchState;
    }
  }

  if (valueChanged) {
    if ((lastHatSwitchState[0] == 0) && (lastHatSwitchState[1] == 0)) {
        Joystick.setHatSwitch(0, -1);
    }
    if (lastHatSwitchState[0] == 1) {
      Joystick.setHatSwitch(0, 0);
    }
    if (lastHatSwitchState[1] == 1) {
      Joystick.setHatSwitch(0, 180);
    }
  } // if the value changed
}
