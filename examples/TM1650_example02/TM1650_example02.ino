#include <Wire.h>
#include <TM1650.h>

/**
* Try example with testing of buttons support:
* 
* press Button1 for increase displayed value (0..9);
* press Button2 for decrease displayed value (0..9);
* press Button3 for change brightness of display;
*/

TM1650 d;

byte dig = 5; // Default display digital
byte bright = 1; // Default brightness of display
bool key1 = false, key2 = false, key3 = false;
bool update_flag = false;

void setup() {
	Wire.begin(); // Join the bus as master

	Serial.begin(19200); // Start serial communication at 19200 for debug statements
	Serial.println("TM1650 Buttons Example Code");

	d.init();
	d.displayChar(0, dig + '0', false);
}

void loop() {
	if (d.getButtons() == 0x44) {
		if (!key1) {
			key1 = true;
			if (dig > 0) dig--;
			update_flag = true;
		}
	} else {
		key1 = false;
	}
	if (d.getButtons() == 0x4c) {
		if (!key3) {
			key3 = true;
			if (dig < 9) dig++;
			update_flag = true;
		}
	} else {
		key3 = false;
	}
	if (d.getButtons() == 0x54) {
		if (!key2) {
			key2 = true;
			bright++;
			if (bright > 7) bright = 1;
			d.setBrightness(bright);
		}
	} else {
		key2 = false;
	}
	if (update_flag) {
		update_flag = false;
		d.displayChar(0, dig + '0', false);
	}
	delay(50);
}

