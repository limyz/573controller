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
// 2019-07-29
//--------------------------------------------------------------------

#include <Joystick.h>
#include <Wire.h>

// LIS3LV02DL Definitions
int _slave_id = 0x1D;
#define CTRL_REG1 0x20

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

  // Initialise I2C for LIS3LV02DL
  Wire.begin();
  Wire.beginTransmission(_slave_id);
  Wire.write(0x20); // CTRL_REG1 (20h)
  Wire.write(0xC7);
  Wire.endTransmission();

  // Initialize Joystick Library
  Joystick.begin();
  /*
  Joystick.setXAxisRange(-8, 8);
  Joystick.setYAxisRange(-8, 8);
  Joystick.setZAxisRange(-8, 8);
 */
  Joystick.setXAxisRange(-255, 255);
  Joystick.setYAxisRange(-255, 255);
  Joystick.setZAxisRange(-255, 255);
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 4;
const int pinToHatSwitchMap = 9;

// Last state of the buttons
int lastButtonState[5] = {0,0,0,0,0};
int lastHatSwitchState[2] = {0,0};

void loop() {
  #define OUT_X 0x29
  #define OUT_Y 0x2B
  #define OUT_Z 0x2D

  bool valueChanged = false;
  byte x_val = i2c_read(OUT_X), y_val = i2c_read(OUT_Y), z_val = i2c_read(OUT_Z);
  
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

  // thanks to @freespace
  // https://forum.arduino.cc/index.php?topic=19779.0

  /* The divisor of x,y, and z are chosen to give the "correct" value at 1g. They are worked out
   by trial and error, but a rough starting point can be calculated as follows:
   
   1. divided by 128 to normalise the range
   2. multiply by 2 since the range is +/- 2, 
     * combined so this gives divided by 64, giving acceleration in gs
   3. multiply by 9.8 to give acceleration in ms/s/s, 
     * combined this gives multiply by 9.8/64 
   4. to make things into nicer integer maths, invert 9.8/64 to give 6.5
   5. now we can truncate and use divisor of 6, an integer, or sacrifice some cycles and use
      a floating value around 6 which gives the "correct" value of 9.8m/s/s for an axis when that
      axis is "pointing" towards the centre of the earth.
   Note I have multiplied everything by 10 implicitly to keep us in int domain
  */
  
  Joystick.setXAxis(x_val * 100 / 55);
  Joystick.setYAxis(y_val * 100 / 55);
  Joystick.setZAxis(z_val * 100 / 63);
  
  /*
  Joystick.setXAxis(x_val * 100 / 8);
  Joystick.setYAxis(y_val * 100 / 8);
  Joystick.setZAxis(z_val * 100 / 8);
  */

  /*
  Joystick.setXAxis(i2c_read(OUT_X));
  Joystick.setYAxis(i2c_read(OUT_Y));
  Joystick.setZAxis(i2c_read(OUT_Z));
  */
}
