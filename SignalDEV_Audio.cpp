/*
	SignalDEV SoundBoard
	Library for playing VGM music using legacy AY-3-891x and SN76489 with an Arduino
	Created by Cecil Meeks (cbmeeks)
	cbmeeks@gmail.com
	http://signaldev.com
	http://meeks.co
	BSD license, all text above must be included in any redistribution

	** NOTE **
	Not all devices have been fully tested.  Unfortunately, this library has also
	gone through several revisions.  I shelved the library for a long time for other things.
	At one point, it 100% worked with AY-3-891x and SN76489.  But, I cannot promise the most
	recent revision (this on) is 100% working.  If there is any interest, please let me 
	know and I will get it going again.  I also have TONS of other types of audio generators
	that I would love to do.  Heck, I might just do it anyway.  :-D
*/

#include <Arduino.h>
#include "SignalDEV_Audio.h"

#if (AY3891X_ENABLED)
	#include "ay3891x.h"
	AY3891x ay389x;
#endif

#if (SN76489_ENABLED)
	#include "sn76489.h"
	SN76489 sn76489;
#endif

/*
	Constructor
*/
SignalDEV_Audio::SignalDEV_Audio() {
	bufferCounter = 0;

#if (AUDIO_DEBUG)
	Serial.begin(9600);
	Serial.println("Audio started...");
#endif
}

void SignalDEV_Audio::begin() {

	//	Defaults
	musicPaused = false;
	musicStopped = false;

	silence();
}


void SignalDEV_Audio::enable() {
#if (AY3891X_ENABLED)
	ay389x.enable();
#endif

#if (SN76489_ENABLED)
	sn76489.enable();
#endif
}



void SignalDEV_Audio::fillBuffer() {
	for(uint8_t i = 0; i < BUFFER_LENGTH; i++ ) {
		buffer[i] = music.read();
	}
}


bool SignalDEV_Audio::isPaused() {
	return musicPaused;
}

bool SignalDEV_Audio::isStopped() {
	return musicStopped;
}

void SignalDEV_Audio::loadVGM(char *filename) {

	if(music) music.close();

	music = SD.open(filename);

	if(music) {
		bufferCounter = 0;
		readVGMHeader();
	}
}


void SignalDEV_Audio::pause() {
	musicPaused = true;
	silence();
}

// how long should we wait  
void SignalDEV_Audio::pause(long samples) {  
	duration = ( (1000.0 / ( 44100.0 / (float)samples ) ) * 1000 );
	startTime = micros();
}

// stream music from SD and play
void SignalDEV_Audio::play() {
	vgm();
}


// read 64 byte header
void SignalDEV_Audio::readVGMHeader() {
	VGMHeader.VGMIdent[0] = char(getByte());	// V
	VGMHeader.VGMIdent[1] = char(getByte());	// G
	VGMHeader.VGMIdent[2] = char(getByte());	// M
	VGMHeader.VGMIdent[3] = char(getByte());	//  

	VGMHeader.EoFOffset = read32() + 4;

	long val = read32();
	unsigned char  buff[4];
	buff[0] = toHex( (unsigned char)val >> 16 );
	buff[1] = toHex( (unsigned char)(val >> 8));
	buff[2] = toHex( (unsigned char)(val >> 4));
	buff[3] = toHex( (unsigned char)(val));
	
	VGMHeader.Version =  
		((int(buff[0])-48) * 1000) + 
		((int(buff[1])-48) * 100) + 
		((int(buff[2])-48) * 10) + 
		(int(buff[3])-48);

	VGMHeader.PSGClock       = read32();
	VGMHeader.YM2413Clock    = read32();
	VGMHeader.GD3Offset      = read32() - 4;  // 4 = size of VGMIdent
	VGMHeader.TotalLength    = read32();
	VGMHeader.LoopOffset     = read32();
	VGMHeader.LoopLength     = read32();
	VGMHeader.RecordingRate  = read32();
	VGMHeader.SNFB           = read16();
	VGMHeader.SNW            = int(getByte());
	getByte();
	VGMHeader.YM2612Clock    = read32();
	VGMHeader.YM2151Clock    = read32();
	VGMHeader.DataOffset     = read32();
	read32();
	read32();
}


void SignalDEV_Audio::resume() {
	musicPaused = false;
}


void SignalDEV_Audio::setSDSSPin(uint8_t pin) {
	sdSS_PIN = pin;
}


void SignalDEV_Audio::silence() {
#if (AY3891X_ENABLED)
	ay389x.disable();
#endif

#if (SN76489_ENABLED)
	sn76489.disable();
#endif
}


/*
	Name:			VGM
	Description:	Processes VGM commands and sends to audio IC's
*/
void SignalDEV_Audio::vgm() {

	//	do nothing if music paused
	if(musicPaused || musicStopped) return;

	//	Enable audio IC's
	enable();

	// if sound needs a delay skip VGM processing instead of 
	// waiting to do other work
	if((micros() - startTime) <= duration) return;   

	uint8_t command = getByte();

	switch (command) {

		/*
			Game Gear PSG stereo
			0x4F dd : Game Gear PSG stereo, write dd to port 0x06
			Spec: 1.70
		*/
 		case VGM_CMD_GG_STEREO:
#if (SN76489_ENABLED)
			sn76489.write(getByte());
#else
			getByte();
#endif
			break;


		/*
			PSG (SN76489/SN76496)
			0x50 dd : PSG (SN76489/SN76496) write value dd
			Spec: 1.70
		*/
		case VGM_CMD_PSG:
#if (SN76489_ENABLED)
			sn76489.write(getByte());
#else
			getByte();
#endif
			break;


		/*
			AY8910
			0xA0 aa dd : AY8910, write value dd to register aa
			Spec: 1.70
		*/
		case VGM_CMD_AY8910:
#if (AY3891X_ENABLED)
			ay389x.write(getByte(), getByte());
#else
			getByte();
			getByte();
#endif
			break;


		/*
			YM2413
			0x51 aa dd : YM2413, write value dd to register aa
			Spec: 1.70
			** NOT IMPLEMENTED **
		*/
		case VGM_CMD_YM2413:
			getByte();
			getByte();
			break;


		/*
			YM2612 port 0
			0x52 aa dd : YM2612 port 0, write value dd to register aa
			Spec: 1.70
			** NOT IMPLEMENTED **
		*/
		case VGM_CMD_YM2612_0:
			getByte();
			getByte();
			break;


		/*
			YM2612 port 1
			0x53 aa dd : YM2612 port 1, write value dd to register aa
			Spec: 1.70
			** NOT IMPLEMENTED **
		*/
		case VGM_CMD_YM2612_1:
			getByte();
			getByte();
			break;


		/*
			YM2151
			0x54 aa dd : YM2151, write value dd to register aa
			Spec: 1.70
			** NOT IMPLEMENTED **
		*/
		case VGM_CMD_2151:
			getByte(); 
			getByte(); 
			break;


		/*
			Wait n samples
  			0x61 nn nn : Wait n samples, n can range from 0 to 65535
  						(approx 1.49 seconds).  Longer pauses than this are
  						represented by multiple wait commands.
			Spec: 1.70
		*/
		case VGM_CMD_WAIT:
			pause(read16());
			break;


		/*
			Wait 735 samples
			0x62 : wait 735 samples (60th of sec), shortcut for 0x61 0xdf 0x02
			Spec: 1.70
		*/
		case VGM_CMD_WAIT_735:
			pause(735);
			break;


		/*
			Wait 882 samples
 			0x63 : wait 882 samples (50th of sec), shortcut for 0x61 0x72 0x03
			Spec: 1.70
		*/
		case VGM_CMD_WAIT_882:
			pause(882);
			break;


		/*
			Override length of 0x62/0x63
			0x64 cc nn nn : override length of 0x62/0x63
			Spec: 1.70
			** Not fully implemented -- Just pause 882 samples **
		*/
		case VGM_PAUSE_BYTE:
			getByte();
			getByte();
			getByte();
			pause(882);
			break;


		/*
			End of sound data
			0x66 : end of sound data
			Spec: 1.70
		*/
		case VGM_CMD_EOF:
			silence();
			if(music) music.close();
			musicStopped = true;
			break;


		/*
			Data block
  			0x67 ... : data block: see Data blocks from 1.70 specs
  			Spec: 1.70
  			** Not fully implemented **
		*/
		case VGM_CMD_DATA_BLOCK:
			getByte(); // compatibility command (0x67?)
			getByte(); // datatype
			break;


		/*
			Wait n+1 samples
			0x7n : wait n+1 samples, n can range from 0 to 15.
			Spec: 1.70
			** Not sure if this is implemented correctly. **
			TODO Check on this spec
		*/
		case 0x70:
		case 0x71:
		case 0x72:
		case 0x73:
		case 0x74:
		case 0x75:
		case 0x76:
		case 0x77:
		case 0x78:
		case 0x79:
		case 0x7A:
		case 0x7B:
		case 0x7C:
		case 0x7D:
		case 0x7E:
		case 0x7F:
			pause(command & 0xF);
			break;


		/*
			PCM data bank write then short wait
			0x8n : YM2612 port 0 address 2A write from the data bank, then wait
				n samples; n can range from 0 to 15. Note that the wait is n,
				NOT n+1. (Note: Written to first chip instance only.)
			Spec: 1.70
			** Not sure if this is implemented correctly **
			TODO Check on this spec
		*/
		case 0x80:
		case 0x81:
		case 0x82: 
		case 0x83: 
		case 0x84: 
		case 0x85: 
		case 0x86: 
		case 0x87: 
		case 0x88: 
		case 0x89: 
		case 0x8A: 
		case 0x8B: 
		case 0x8C: 
		case 0x8D: 
		case 0x8E: 
		case 0x8F: 
			pause(command & 0xF);
			break;


		/*
			Seek to offset
			0xE0 dddddddd : seek to offset dddddddd (Intel byte order)
							in PCM data bank
			Spec: 1.70
			TODO	Not implemented correctly
		*/
		case VGM_CMD_YM2612_PCM_SEEK:
			read32();
			break;


		/*
			Nothing matches...
		*/
		default:
			break;
	}
}


/*
	Private Methods
*/

// get VGM data from buffer
uint8_t SignalDEV_Audio::getByte() {

	if (bufferCounter == BUFFER_LENGTH) {
		fillBuffer();
		bufferCounter = 0;
	}

	return buffer[bufferCounter++];
}


//	read a 16-bit number from 2 bytes
unsigned int SignalDEV_Audio::read16() {
	return getByte() + ( getByte() << 8 );
}

//	read a 32-bit number from 4 bytes
long SignalDEV_Audio::read32() {

	long v0 = long(getByte());
	long v1 = long(getByte());  
	long v2 = long(getByte());  
	long v3 = long(getByte());
	
	return v0 + (v1 << 8) + (v2 << 16) + (v3 << 24);
}

// convert number to hexadecimal 255 = FF
char SignalDEV_Audio::toHex(int h) {
	h &= 0xf;
	if( h < 10 ) return (h + '0');
	return (h - 10 + 'A');
}


