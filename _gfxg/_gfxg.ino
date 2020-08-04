//--------------------------------------------------------------------
// For use with a 573 or GH Guitar Controller
//
// This sketch maps a LIS3LV02DL accelerometer via I2C and uses 7 digital
// inputs - 5 buttons and a 2 hat switches for the pick.
//
// All digital pins are grounded when they are pressed.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Micro only.
//
// by lyzzz
// 2020-03-31
//--------------------------------------------------------------------

#include <Joystick.h>
#include <Wire.h>

// LIS3LV02DL Definitions
int _slave_id = 0x1D;
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  5, 1,                  // Button Count, Hat Switch Count
  true, true, true,      // X, Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

byte i2c_read(byte address) {
  Wire.beginTransmission(_slave_id);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(_slave_id, 1);
  while(Wire.available()) {
   return Wire.read();
  }
}

void setup() {
  // Initialize Pins
  // Pins 2 and 3 -> Guitar Accelerometer (I2C)
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  // Pins 5 to 9 -> Guitar R, G, B, Y, P Buttons
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  // Pins 9 to 10 -> Guitar Pick
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  // Initialise I2C for LIS3LV02DL
  Wire.begin();
  Wire.beginTransmission(_slave_id);
  Wire.write(CTRL_REG1);
  Wire.write(0xF7);
  Wire.endTransmission();

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-2048, 2048);
  Joystick.setYAxisRange(-2048, 2048);
  Joystick.setZAxisRange(-2048, 2048);
}

byte keys[] = {6, 4, 5, 7, 8};
byte pick[] = {9 ,10};
int lastButtonState[5] = {0,0,0,0,0};
int lastHatSwitchState[2] = {0,0};

void loop() {
  #define OUTX_L 0x28
  #define OUTX_H 0x29
  #define OUTY_L 0x2A
  #define OUTY_H 0x2B
  #define OUTZ_L 0x2C
  #define OUTZ_H 0x2D

  bool valueChanged = false;
  byte x_val_l = i2c_read(OUTX_L), y_val_l = i2c_read(OUTY_L), z_val_l = i2c_read(OUTZ_L);
  byte x_val_h = i2c_read(OUTX_H), y_val_h = i2c_read(OUTY_H), z_val_h = i2c_read(OUTZ_H);

  // Read pin values
  for (int index = 0; index < 5; index++) {
    int currentButtonState = !digitalRead(keys[index]);
    if (currentButtonState != lastButtonState[index]) {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  for (int index = 0; index < 2; index++) {
    int currentHatSwitchState = digitalRead(pick[index]);
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
  }

  Joystick.setXAxis(x_val_l | x_val_h << 8);
  Joystick.setYAxis(y_val_l | y_val_h << 8);
  Joystick.setZAxis(z_val_l | z_val_h << 8);
}
