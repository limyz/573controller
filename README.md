# 573controller

This repository houses several .ino files for use with an Arduino. Supported music game controllers include:
* _gfxg 

Allows you to use an Arduino Leonardo or Micro to transform a Guitar Hero/GuitarFreaks/Gitadora guitar into a USB game controller
* _iidx

Allows you to use an Arduino Leonardo or Micro to transform an IIDX controller into a USB game controller with full support for [beatmania IIDX INFINITAS](https://p.eagate.573.jp/game/eac2dx/infinitas).
* _iidx_2p

Similar to _iidx but with buttons remapped from E1/E2 to E3/E4 for use with doubles play (DP).

## Requirements
* Arduino Leonardo or Micro
* [Arduino Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary)

If you are using _iidx, it additionally requires:
* [Quadrature Encoder Library for Arduino](https://github.com/PaulStoffregen/Encoder)
* Replacement of `boards.txt` located in your `Arduino/hardware/avr` directory. This modifies the pid (Product ID) and vid (Vendor ID) for [beatmania IIDX INFINITAS](https://p.eagate.573.jp/game/eac2dx/infinitas) to accept in-game input.
