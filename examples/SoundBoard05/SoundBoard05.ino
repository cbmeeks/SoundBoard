/*
	SignalDEV SoundBoard
	Library for playing VGM music using legacy AY-3-891x and SN76489 with an Arduino
	Created by Cecil Meeks (cbmeeks)
	cbmeeks@gmail.com
	http://signaldev.com
	http://meeks.co
	BSD license, all text above must be included in any redistribution

	This is just an example of using the library.  The songs below are the VGM files
	I have used for testing.  IIRC, almost (if not all) of them worked 100% at one time.
	Please do not redistribute any of these VGM files without permission from the authors.

	Also, this library does not currently support compression of the VGM file.


	SD Wiring

	SD_PIN_13	= SCK
	SD_PIN_12	= MISO
	SD_PIN_11	= MOSI
	SD_PIN_10	= SS (Slave Select)
	SD_PIN_5V	= 5V source
	SD_PIN_GND	= GND source

*/

#include <SPI.h>
#include <SD.h>
#include "SignalDEV_Audio.h"

//	Library objects
SignalDEV_Audio audio;
File root;

uint8_t SDSS_PIN = 10;

void setup() {

	pinMode(SDSS_PIN, OUTPUT);
	SD.begin();

	audio.begin();
	audio.silence();
	audio.setSDSSPin(SDSS_PIN);


	// audio.loadVGM("bat01.vgm");		//	Batman:Revenge of the Joker (2612)


	// audio.loadVGM("ab01.vgm");
	// audio.loadVGM("ab02.vgm");
	// audio.loadVGM("ab03.vgm");
	// audio.loadVGM("ab04.vgm");
	// audio.loadVGM("ab05.vgm");
	// audio.loadVGM("ab06.vgm");
	// audio.loadVGM("ab07.vgm");
	// audio.loadVGM("ab08.vgm");
	// audio.loadVGM("ab09.vgm");
	// audio.loadVGM("ab10.vgm");

	// audio.loadVGM("al03.vgm");			//	Aladdin
	// audio.loadVGM("alarab.vgm");			//	Aladdin Arabian Nights

	// audio.loadVGM("astro.vgm");			//	Astro Warriors
	// audio.loadVGM("astro2.vgm");
	// audio.loadVGM("astro3.vgm");

	// audio.loadVGM("bb01.vgm");			//	Bubble Bobble
	// audio.loadVGM("bb02.vgm");
	// audio.loadVGM("bb03.vgm");
	// audio.loadVGM("bb04.vgm");
	// audio.loadVGM("bb05.vgm");
	// audio.loadVGM("bb06.vgm");
	// audio.loadVGM("bb07.vgm");
	// audio.loadVGM("bb08.vgm");
	// audio.loadVGM("bb09.vgm");
	// audio.loadVGM("bb10.vgm");
	// audio.loadVGM("bb11.vgm");
	// audio.loadVGM("bb12.vgm");

	// audio.loadVGM("bubble01.vgm");		//	Bubble Bobble (MSX) 8910
	// audio.loadVGM("bubble02.vgm");
	// audio.loadVGM("bubble03.vgm");
	// audio.loadVGM("bubble04.vgm");
	// audio.loadVGM("bubble05.vgm");
	// audio.loadVGM("bubble06.vgm");
	// audio.loadVGM("bubble07.vgm");
	// audio.loadVGM("bubble08.vgm");
	// audio.loadVGM("bubble09.vgm");
	// audio.loadVGM("bubble10.vgm");


	// audio.loadVGM("castle.vgm");
	// audio.loadVGM("bios.vgm");
	
	// audio.loadVGM("dd02.vgm");			//	Double Dragon

	// audio.loadVGM("ff01.vgm");			//	Final Fantasy 8910
	// audio.loadVGM("ff02.vgm");


	// audio.loadVGM("gal01.vgm");			//	Galaga
	// audio.loadVGM("gal02.vgm");

	// audio.loadVGM("ghostshp.vgm");


	// audio.loadVGM("jny01.vgm");				// JOURNEY!!  (8910 x 2!!)
	// audio.loadVGM("jny02.vgm");					//  Don't stop beliving!
	// audio.loadVGM("jny03.vgm");
	// audio.loadVGM("jny04.vgm");
	// audio.loadVGM("jny05.vgm");
	// audio.loadVGM("jny06.vgm");
	// audio.loadVGM("jny07.vgm");
	// audio.loadVGM("jny08.vgm");


	// audio.loadVGM("mj06.vgm");				// Moonwalker (2612)


	// audio.loadVGM("nem01.vgm");		// Nemesis / Gradius (MSX) 8910
	// audio.loadVGM("nem02.vgm");	
	// audio.loadVGM("nem03.vgm");	
	// audio.loadVGM("nem04.vgm");	
	// audio.loadVGM("nem05.vgm");	
	// audio.loadVGM("nem06.vgm");	
	// audio.loadVGM("nem07.vgm");	
	// audio.loadVGM("nem08.vgm");		
	// audio.loadVGM("nem09.vgm");	
	// audio.loadVGM("nem10.vgm");	
	// audio.loadVGM("nem11.vgm");	
	// audio.loadVGM("nem12.vgm");	
	// audio.loadVGM("nem13.vgm");	
	// audio.loadVGM("nem14.vgm");




	// audio.loadVGM("pen01.vgm");			// Penguin Adventure (MSX) 8192
	// audio.loadVGM("pen02.vgm");
	// audio.loadVGM("pen03.vgm");
	// audio.loadVGM("pen04.vgm");
	// audio.loadVGM("pen05.vgm");




	// audio.loadVGM("pop01.vgm");			//	Prince of Persia
	// audio.loadVGM("pop02.vgm");
	// audio.loadVGM("pop03.vgm");
	// audio.loadVGM("pop04.vgm");
	// audio.loadVGM("pop05.vgm");
	// audio.loadVGM("pop06.vgm");
	// audio.loadVGM("pop07.vgm");
	// audio.loadVGM("pop08.vgm");
	// audio.loadVGM("pop09.vgm");

	// audio.loadVGM("pwrplnt.vgm");
	// audio.loadVGM("missing.vgm");	

	// audio.loadVGM("ras01.vgm");			//	Rastan 8910
  // audio.loadVGM("ras02.vgm");
	// audio.loadVGM("ras03.vgm");
	// audio.loadVGM("ras04.vgm");
	// audio.loadVGM("ras05.vgm");


	// audio.loadVGM("rtype.vgm");		//	R-Type
	// audio.loadVGM("rtype2.vgm");

	// audio.loadVGM("sor03.vgm");		//	The Sorcerian

	audio.loadVGM("shin01.vgm");		//	Shinobi    8910
	// audio.loadVGM("shin02.vgm");	
	// audio.loadVGM("shin03.vgm");	
	// audio.loadVGM("shin04.vgm");


	// audio.loadVGM("space01.vgm");		//	Space Manbow (8910)  Not working?

	// audio.loadVGM("start.vgm");


	// audio.loadVGM("vamp01.vgm");		// Vampire Killer (MSX) 8910
	// audio.loadVGM("vamp02.vgm");
	// audio.loadVGM("vamp03.vgm");		//	Classic and spooky.  :-)
	// audio.loadVGM("vamp04.vgm");		//	Wicked Child?  (Good)
	// audio.loadVGM("vamp05.vgm");
	// audio.loadVGM("vamp06.vgm");		// GO3OD
	// audio.loadVGM("vamp07.vgm");
	// audio.loadVGM("vamp08.vgm");	
	// audio.loadVGM("vamp09.vgm");
	// audio.loadVGM("vamp10.vgm");
	// audio.loadVGM("vamp11.vgm");
	// audio.loadVGM("vamp12.vgm");
	// audio.loadVGM("vamp13.vgm");
	// audio.loadVGM("vamp14.vgm");
	// audio.loadVGM("vamp15.vgm");


	// audio.loadVGM("tet01.vgm");		//	Tetris
	// audio.loadVGM("tet02.vgm");


	// audio.loadVGM("tf4.vgm");
	// audio.loadVGM("zeldaend.vgm");



	// MsTimer2::set(1, play);
 //  	MsTimer2::start();

	// Timer1.initialize(1000); 
	// Timer1.attachInterrupt( play ); 


}



void loop() {

	audio.play();

}






