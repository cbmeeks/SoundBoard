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
#include "ay3891x.h"


/*
	Constructor
*/
AY3891x::AY3891x() {

	pinMode(AY3891x_SS, OUTPUT);
	digitalWrite(AY3891x_SS, HIGH);

	SPI.begin();						// activate SPI bus
	SPI.setBitOrder(MSBFIRST);

	pinMode(AY38912_BC1, OUTPUT);
	pinMode(AY38912_BDIR, OUTPUT);
	pinMode(AY38912_RESET, OUTPUT);

	digitalWrite(AY38912_RESET, LOW); // LOW by default (silence)

}

void AY3891x::disable() {
	digitalWrite(AY38912_RESET, LOW);
}

void AY3891x::enable() {
	digitalWrite(AY38912_RESET, HIGH);
}


void AY3891x::setSDSSPin(uint8_t pin) {
	sdSS_PIN = pin;
}


/*
	Write data to an AY-3-8910 (or its variations like 8912)
	
	Because the VGM spec states that data is stored in Intel format (big Endian)
	we send the data before the address
*/
void AY3891x::write(uint8_t data, uint8_t address) {

	//	Enable AY and disable SD
	digitalWrite(sdSS_PIN, HIGH);
	digitalWrite(AY3891x_SS, LOW);


	digitalWrite(AY38912_BC1, LOW);
	digitalWrite(AY38912_BDIR, LOW);
	delayMicroseconds(10);

	digitalWrite(AY38912_BC1, HIGH);
	digitalWrite(AY38912_BDIR, HIGH);
	delayMicroseconds(10);


	digitalWrite(AY3891x_SS, LOW);
	SPI.transfer(address);
	digitalWrite(AY3891x_SS, HIGH);


	digitalWrite(AY38912_BC1, LOW);
	digitalWrite(AY38912_BDIR, LOW);
	delayMicroseconds(10);

	digitalWrite(AY38912_BC1, LOW);
	digitalWrite(AY38912_BDIR, LOW);


	digitalWrite(AY3891x_SS, LOW);
	SPI.transfer(data);
	digitalWrite(AY3891x_SS, HIGH);

	
	digitalWrite(sdSS_PIN, LOW);


	digitalWrite(AY38912_BDIR, HIGH);
	digitalWrite(AY38912_BC1, LOW);
	delayMicroseconds(10);

	digitalWrite(AY38912_BC1, LOW);
	digitalWrite(AY38912_BDIR, LOW);

}

