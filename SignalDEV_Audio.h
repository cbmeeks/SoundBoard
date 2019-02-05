
/*
	SignalDEV SoundBoard
	Library for playing VGM music using legacy AY-3-891x and SN76489 with an Arduino
	Created by Cecil Meeks (cbmeeks)
	cbmeeks@gmail.com
	http://signaldev.com
	http://meeks.co
	BSD license, all text above must be included in any redistribution

	Special Thanks to http://blog.luis.net
	Special Thanks to http://www.smspower.org/uploads/Music/vgmspec161.txt

	//	TODO	Check on newer 1.70 spec

*/
#ifndef SIGNALDEV_AUDIO_H
#define SIGNALDEV_AUDIO_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>


#define AUDIO_DEBUG		1


/*
	HARDWARE DEFINES
	You can enable/disable various music IC's here.
	Be sure to define the proper pins within the IC's main headers
*/

#define AY3891X_ENABLED			1
#define SN76489_ENABLED			0


//	Fast pin switching macros
#define CLR(x, y)		(x &= (~(1<<y)))
#define SET(x, y)		(x |= (1<<y))
#define __BCPORT__		PORTD


#define BUFFER_LENGTH					30

/*
	VGM COMMANDS
*/
#define VGM_HEADER                      "Vgm "
#define VGM_CMD_GG_STEREO               0x4F
#define VGM_CMD_PSG                     0x50
#define VGM_CMD_YM2413                  0x51
#define VGM_CMD_YM2612_0                0x52
#define VGM_CMD_YM2612_1                0x53
#define VGM_CMD_2151                    0x54
#define VGM_CMD_WAIT                    0x61
#define VGM_CMD_WAIT_735                0x62
#define VGM_CMD_WAIT_882                0x63
#define VGM_PAUSE_BYTE                  0x64
#define VGM_CMD_EOF                     0x66
#define VGM_CMD_DATA_BLOCK              0x67
#define VGM_CMD_AY8910					0xA0
#define VGM_CMD_YM2612_PCM_SEEK         0xE0


class SignalDEV_Audio {
	public:
		SignalDEV_Audio();
		void begin();
		void enable();
		void fillBuffer();
		bool isPaused();
		bool isStopped();
		void loadVGM(char *filename);
		void pause();
		void pause(long samples);
		void resume();
		void play();
		void readVGMHeader();
		void silence();

		void setSDSSPin(uint8_t pin);
	private:

		// VGM file header
		struct TVGMHeader{
			char VGMIdent[4];			// "Vgm "
			long EoFOffset;				// relative offset (from this point, 0x04) of the end of file
			long Version;				// 0x00000101 for 1.01
			long PSGClock;				// typically 3579545, 0 for no PSG
			long FMClock;				// typically , 0 for no FM
			long YM2413Clock;			// typically 3579545, 0 for no FM
			long YM2151Clock;			// typically 3579545, 0 for no FM
			long YM2612Clock;			// typically 3579545, 0 for no FM
			long GD3Offset;				// relative offset (from this point,0x14) of Gd3 tag,0 if not present
			long TotalLength;			// in samples
			long LoopOffset;			// relative again (to 0x1c), 0 if no loop
			long LoopLength;			// in samples, 0 if no loop	
			long RecordingRate;	        
			long SNFB;	        
			long SNW;
			long DataOffset;

			//	TODO	Add other fields here or a way to skip past them (skip probably better)
			
			long AY8910Clock;			// I've seen 1/2 of NTSC frequency used (1,789,773)

		} VGMHeader;

		bool musicPaused;
		bool musicStopped;
		unsigned long startTime;		// keep track of elapsedTime for pause command
		unsigned long duration;
		uint8_t getByte();
		uint8_t buffer[BUFFER_LENGTH];	// VGM instruction buffer
		uint8_t bufferCounter;			// how many bytes have we chewed off buffer
		unsigned int read16();
		long read32();
		char toHex(int h);
		File music;
		void vgm();

		uint8_t sdSS_PIN;				// SD card slave select pin
};

#endif
