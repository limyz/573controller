# 573controller

This repository houses several Arduino .ino files for use with an Arduino Leonardo or Micro to transform it into music game controller. Supported controllers include:

* _ddr & _ddrTest

Allows you to transform an it into a USB game controller consisting of 4 buttons. The actual machine has 16 sensors (4 for each pad) for input. Use `_ddrTest` to determine if the indivdual sensors are working.

* _gfxg 

Allows you to transform it into a a USB game controller for use with [Clone Hero](https://clonehero.net)/[DTXAL](http://senamih.com/dtxal)/Guitar Hero/GuitarFreaks/Gitadora. For instructions on how to convert an existing guitar into one, [check out 573controller's wiki](https://github.com/limyz/573controller/wiki/DIY-Guitar).

To see the controller in action, do visit [APPROVED DTX Gaming over at YouTube, where this live stream specifically shows it in use](https://youtu.be/GGR9hHf-6ow?t=180).

* _iidx

Allows you to transform it into a IIDX controller with full native support for [beatmania IIDX INFINITAS](https://p.eagate.573.jp/game/eac2dx/infinitas).

* _iidx_2p

Similar to _iidx but with buttons remapped from E1/E2 to E3/E4 for use with doubles play (DP). For players using the 2P side for single play, simply modify E3/E4 to E1/E2 button mappings.

For a demostration, do visit [nsa_spy99 over at Twitch, where it shows native mapping and performance in-game](https://www.twitch.tv/nsa_spy99).

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

## Donations Appreciated!

[If you appreciate my work, why not treat me a beer?](https://paypal.me/limyz)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://paypal.me/limyz)
