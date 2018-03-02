/**
 * PLed.h - Library for operating various LEDs in a non blocking way
 * (c) 2018 Christian Grieger
 * GNU GENERAL PUBLIC LICENSE
 */

#ifndef PLED_H
#define PLED_H

#include <Arduino.h>

class PLed
{
	public:
		/**
		 * Constructor which resets all relevant values and connects
         * the LED to the right pin of the Arduino.
		 *
         * pin    Number of the pin to be connected on the Arduino (has to be PWM capable)
		 */
		PLed (byte pin);

		/**
		 * Optional function to set min and max brightness of the LEDs,
		 * if you like to limit these values.
		 *
		 * minBrightness   Minimal value the LED should be powered with [0..255]
		 * maxBrightness   Maxmial value the LED should be powered with [0..255]
		 */
		void setBrightness (byte minBrightness, byte maxBrightness);

		/**
		 * Activates the LED in blinking mode
		 *
		 * delayOn       Delay in milliseconds the LED stays ON
		 * delayOff      Delay in milliseconds the LED stays OFF
		 * iterations    amount of blink cycles to be made
		 */
		void activateBlink (unsigned int delayOn, unsigned int delayOff, int iterations);
		void activateBlink (unsigned int delayOn, unsigned int delayOff);

		/**
		 * Activates the LED in fading mode
		 *
		 * fadeTime      Duration of a fade cycle in seconds
		 * iterations    amount of fade cycles to be made
		 */
		void activateFade (byte fadeTime, int iterations);
		void activateFade (byte fadeTime);

		/**
		 * Stops all LED actions and turns it off
		 */
		void stop ();

		/**
		 * Update routine which should be called in the main loop()-function
		 */
		void update ();

		static const byte MODE_BLINK;
		static const byte MODE_FADE;
		static const bool DIRECTION_RISING;
		static const bool DIRECTION_FALLING;

	protected:
		byte _pin;
		byte _mode;
		byte _minBrightness;
		byte _maxBrightness;
		byte _brightness;
		bool _hasBrightnessChanged;
		bool _direction;
		unsigned int _delayOn;
		unsigned int _delayOff;
		unsigned int _delayFadeStep;
		int _iterations;
		unsigned long _lastAction;
};

#endif