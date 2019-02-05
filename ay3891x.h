/*
	SignalDEV SoundBoard
	Library for playing VGM music using legacy AY-3-891x and SN76489 with an Arduino
	Created by Cecil Meeks (cbmeeks)
	cbmeeks@gmail.com
	http://signaldev.com
	http://meeks.co
	BSD license, all text above must be included in any redistribution
*/
/******************************************************************************
	Library for the AY-3-8910 (or variants such as 8912/8913)
	This library assumes you are connecting via a 74595 shift register.
	Other connections methods may come in the future.

	Written by Cecil Meeks ( cbmeeks@gmail.com | @cbmeeks | http://meeks.co )
	BSD license, all text above must be included in any redistribution
******************************************************************************/

#ifndef AY3891X_H
#define AY3891X_H

#include <Arduino.h>
#include "SPI.h"

class AY3891x {

public:
	AY3891x();
	void enable();
	void disable();
	void setSDSSPin(uint8_t pin);
	void write(uint8_t data, uint8_t address);

private:

	//	SD Slave Select Pin (used for streaming VGM off SD card)
	uint8_t sdSS_PIN;

	//	Enter the appropriate pin values below
	uint8_t AY3891x_SS		= 9;

	//	AY-3-8910/2/3 PSG 	(BC2 is usually HIGH at least on 8912)
	uint8_t AY38912_BC1		= 6;
	uint8_t AY38912_BDIR	= 5;
	uint8_t AY38912_RESET	= 4;

};

#endif
