# 573controller

This repository houses several Arduino .ino files for use with an Arduino Leonardo or Micro to transform it into music game controller. Supported controllers include:

* _gfxg 

Allows you to transform it into a a USB game controller for use with [Clone Hero](https://clonehero.net)/[DTXAL](http://senamih.com/dtxal)/Guitar Hero/GuitarFreaks/Gitadora.

For instructions on how to convert an existing guitar into one, [check the wiki here](https://github.com/limyz/573controller/wiki/DIY-Guitar).

* _iidx

Allows you to transform it into a IIDX controller with full native support for [beatmania IIDX INFINITAS](https://p.eagate.573.jp/game/eac2dx/infinitas).

* _iidx_2p

Similar to _iidx but with buttons remapped from E1/E2 to E3/E4 for use with doubles play (DP). For players using the 2P side for single play, simply modify E3/E4 to E1/E2 button mappings.

* _sdvx

Allows you to transform it into a SDVX controller with full native support for [SOUND VOLTEX III](https://p.eagate.573.jp/game/eacsdvx/iii).

## Requirements
* Arduino Leonardo or Micro
* [Arduino Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary)

If you are using _iidx, it additionally requires:
* [Quadrature Encoder Library for Arduino](https://github.com/PaulStoffregen/Encoder)
* Replacement of `boards.txt` located in your `Arduino/hardware/avr` directory. This allows [beatmania IIDX INFINITAS](https://p.eagate.573.jp/game/eac2dx/infinitas) to accept in-game input natively.

If you are using _sdvx, it additionally requires:
* [Quadrature Encoder Library for Arduino](https://github.com/PaulStoffregen/Encoder)
* Replacement of `boards.txt` located in your `Arduino/hardware/avr` directory. This allows [SOUND VOLTEX III](https://p.eagate.573.jp/game/eacsdvx/iii) to accept in-game input natively.
