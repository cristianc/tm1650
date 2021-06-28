#include <Arduino.h>
#include <TM1650.h>

/**
* Try example with testing of buttons support:
* 
* press Button1 for decrease displayed value (0..9)
* press Button2 for change brightness of display
* press Button3 for increase displayed value (0..9)
*/

TM1650 tm1650;

byte dig = 5;    // Default displayed value
byte bright = 4; // Default brightness of display
bool key1 = false, key2 = false, key3 = false;
bool update_flag = false;

void setup() {
    Serial.begin(19200); // Start serial communication at 19200 for debug statements
    Serial.println("TM1650 Buttons Example Code");

    Wire.begin(); // Join the bus as master

    tm1650.init();
    tm1650.setBrightness(bright);
    tm1650.displayChar(0, 'H', false);
    tm1650.displayChar(1, 'I', false);
    tm1650.displayChar(2, '-', false);
    tm1650.displayChar(3, dig + '0', false);
}

void loop() {
    byte buttons = tm1650.getButtons();
    if (buttons == 0x44) {
        if (!key1) {
            key1 = true;
            if (dig > 0) dig--;
            update_flag = true;
        }
    } else {
        key1 = false;
    }

    if (buttons == 0x4c) {
        if (!key2) {
            key2 = true;
            bright++;
            if (bright > TM1650_MAX_BRIGHT) {
                bright = TM1650_MIN_BRIGHT;
            }
            tm1650.setBrightness(bright);
        }
    } else {
        key2 = false;
    }

    if (buttons == 0x54) {
        if (!key3) {
            key3 = true;
            if (dig < 9) dig++;
            update_flag = true;
        }
    } else {
        key3 = false;
    }

    if (update_flag) {
        update_flag = false;
        tm1650.displayChar(3, dig + '0', false);
    }

    delay(50);
}
