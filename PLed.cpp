/**
 * PLed.cpp - Library for operating various LEDs in a non blocking way
 * (c) 2018 Christian Grieger
 * GNU GENERAL PUBLIC LICENSE
 */

#include <Arduino.h>
#include <PLed.h>

const byte PLed::MODE_BLINK = 1;
const byte PLed::MODE_FADE  = 2;
const bool PLed::DIRECTION_RISING  = true;
const bool PLed::DIRECTION_FALLING = false;

PLed::PLed (byte pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
	_mode = 0;
	_minBrightness = 0;
	_maxBrightness = 255;
	_brightness = 0;
	_hasBrightnessChanged = false;
	_lastAction = 0;
	_direction = PLed::DIRECTION_RISING;
	_delayOn = 0;
	_delayOff = 0;
	_delayFadeStep = 0;
	_iterations = 0;
}

void PLed::setBrightness (byte minBrightness, byte maxBrightness)
{
	_minBrightness = minBrightness;
	_maxBrightness = max(minBrightness, maxBrightness);
	_brightness	= max(_minBrightness, min(_brightness, _maxBrightness));
}

void PLed::activateBlink (unsigned int delayOn, unsigned int delayOff, int iterations)
{
	_mode = PLed::MODE_BLINK;
	_delayOn = max(1, delayOn);
	_delayOff = max(1, delayOff);
	_iterations = iterations;
	_lastAction = millis();
	_direction = PLed::DIRECTION_RISING;
}

void PLed::activateBlink (unsigned int delayOn, unsigned int delayOff)
{
	activateBlink(delayOn, delayOff, -1);
}

void PLed::activateFade (byte fadeTime, int iterations)
{
	_mode = PLed::MODE_FADE;
	_delayOn = 0;
	_delayOff = 0;

	// calculate fading delay per step
	byte steps = _maxBrightness - _minBrightness;
	_delayFadeStep = (int)(fadeTime*1000 / steps);

	_iterations = iterations;
	_lastAction = millis();
}

void PLed::activateFade (byte fadeTime)
{
	activateFade (fadeTime, -1);
}

void PLed::stop ()
{
	_mode = 0;
	_brightness = 0;
	analogWrite(_pin, _brightness);
}

void PLed::update ()
{
	if (_mode == 0) {
		return;
	}

	switch(_mode)
	{
		case PLed::MODE_BLINK:
			if (_direction == PLed::DIRECTION_RISING) {
				if (millis() - _lastAction > _delayOff) {
					_brightness = _maxBrightness;
					_hasBrightnessChanged = true;
					_direction = !_direction;
					_lastAction += _delayOff;
				}
			} else {
				if (millis() - _lastAction > _delayOn) {
					_brightness = _minBrightness;
					_hasBrightnessChanged = true;
					_direction = !_direction;
					_lastAction += _delayOn;
					if (_iterations > 0) {
						_iterations--;
					}
				}
			}
		break;

		case PLed::MODE_FADE:
			if (millis() - _lastAction > _delayFadeStep) {
				if (_direction == PLed::DIRECTION_RISING) {
					_brightness++;
					_hasBrightnessChanged = true;
					_lastAction += _delayFadeStep;
					if (_brightness >= _maxBrightness) {
						_direction = !_direction;
					}
				} else {
					_brightness--;
					_hasBrightnessChanged = true;
					_lastAction += _delayFadeStep;
					if (_brightness <= _minBrightness) {
						_direction = !_direction;
						if (_iterations > 0) {
							_iterations--;
						}
					}
				}
			}
			break;
	}

	if (_iterations == 0) {
		_hasBrightnessChanged = false;
		this->stop();
	}

	if (_hasBrightnessChanged == true) {
		analogWrite(_pin, _brightness);
	}
}
