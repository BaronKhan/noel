N.O.E.L (Nimble On Extended Legs)
===========

A Bluetooth remote-control hexapod running on an Arduino Nano, programmed in C++17.

[Demo Video (YouTube)](https://www.youtube.com/watch?v=OCahM36BvgQ)

Hardware
---------

* Arduino Nano - ATmega328P (Old Bootloader)
* Arduino Nano I/O Expansion Breakout Board
* HC-06 Wireless Bluetooth Serial Transceiver
* 3 Servo Motors
* 9V Battery

Compilation
---------

Compile using the Arduino IDE with the `-std=gnu++17` flag added to `compiler.cpp.flags` in
`hardware/arduino/avr/platform.txt`.
