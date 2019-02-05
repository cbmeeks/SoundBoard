/*
	SignalDEV SoundBoard
	Library for playing VGM music using legacy AY-3-891x and SN76489 with an Arduino
	Created by Cecil Meeks (cbmeeks)
	cbmeeks@gmail.com
	http://signaldev.com
	http://meeks.co
	BSD license, all text above must be included in any redistribution
*/
#include <Arduino.h>
#include "sn76489.h"


/*
	Constructor
*/
SN76489::SN76489() {

	// sr74595.begin(SR_74595_SI, SR_74595_RCK, SR_74595_SCK);

	pinMode(SN76489_PIN_WE, OUTPUT);
	pinMode(SN76489_PIN_CE, OUTPUT);

	digitalWrite(SN76489_PIN_CE, LOW);
	digitalWrite(SN76489_PIN_WE, HIGH);
}

void SN76489::disable() {

}

void SN76489::enable() {

}

/*
	Write data to an SN76489
*/
void SN76489::write(uint8_t data) {

	// sr74595.write(data);

	//	Strobe SN76489_PIN_WE
	digitalWrite(SN76489_PIN_WE, LOW);
	delayMicroseconds(5);
	digitalWrite(SN76489_PIN_WE, HIGH);
}

