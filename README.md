# PLed

PLed is an Arduino library written in C++ which allows you to operate more than one LED at the same time in a non blocking way.

## Features
  - Blinking a LED with different On/Off delay times
  - Fading a LED with a given amount of fading time
  - Set minimum and maximum brightness of every LED
  - Give an optional number of iterations how often the LEDs should blink or fade

## How to install the library
 - Download the lastes release of this library from github
 - Open the Arduino IDE
 - Go to the Library Manager (available from IDE version 1.6.2): Open the IDE and click to the "Sketch" menu and then Include Library > Add .ZIP Library...
 - Importing the .zip file of this library and you´re done


## Setup
see: http://elektro.turanis.de/html/prj0024.html

## Usage

Include the header file of the library:
```c
#include <PLed.h>
```

Add some LEDs you want to operate:
```c
PLed led1(PIN_LED1);
PLed led2(PIN_LED2);
PLed led3(PIN_LED3);
```

Activate the LED operations in the main setup() or loop() function:
```c
led1.activateBlink(100, 1000);
led2.activateBlink(500, 79, 10);
led3.activateFade(3);
```

Enter the update function in the main loop() function:
```c
PLed::update();
```

Examine the "example.ino" for a complete sample.