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
	Library for the SN76489 
	This library assumes you are connecting via a 74595 shift register.
	Other connections methods may come in the future.

	Written by Cecil Meeks ( cbmeeks@gmail.com | @cbmeeks | http://meeks.co )
	BSD license, all text above must be included in any redistribution
******************************************************************************/

#ifndef SN76489_H
#define SN76489_H

#include <Arduino.h>
// #include "sr74595.h"

#define UNUSED_PIN	99

class SN76489 {

public:
	SN76489();
	void enable();
	void disable();
	void write(uint8_t value);

private:


	//	Enter the appropriate pin values below

	uint8_t SR_74595_SI	 	= 9;	//	Serial Data Input
	uint8_t SR_74595_RCK 	= 8;	//	Storage Register Clock Input (Latch)
	uint8_t SR_74595_SCK	= 7;	//	Shift Register Clock Input (Clock)

//	SN7648 Pin Assignment
	uint8_t SN76489_PIN_WE 	= 3;
	uint8_t SN76489_PIN_CE 	= 2;
};

#endif