/**
 * Example sketch for testing the PLed-Library with three different LEDs
 * (c) 2018 Christian Grieger
 * GNU GENERAL PUBLIC LICENSE
 */

#define PIN_LED1 9
#define PIN_LED2 10
#define PIN_LED3 11

#include <PLed.h>

PLed led1 = PLed(PIN_LED1);
PLed led2 = PLed(PIN_LED2);
PLed led3 = PLed(PIN_LED3);

void setup()
{
	led1.setBrightness (0, 5);
	led1.activateBlink(100, 100);

	led2.activateBlink(500, 279, 10);

	led3.activateFade(3);
}

void loop()
{
	led1.update();
	led2.update();
	led3.update();
}