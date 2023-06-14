#include <Arduino.h>
#include <TM1650.h>

/**
* Try example with testing of buttons support:
* 
* press Button1 to switch letters into lower/upper case
* press Button2 to turn dots on/off
* press Button3 to make display blinking or not blinking
* press Button4 to decrease displayed value (0..9)
* press Button5 to increase displayed value (0..9)
* press Button6 to change brightness of display
* press Button7 to turn display on or off
*/

TM1650 tm1650;

char firstChar = 'H';
char secondChar = 'I';
byte dig = 5;    // Default displayed value
byte bright = 4; // Default brightness of display
bool key1 = false, key2 = false, key3 = false, key4 = false, key5 = false, key6 = false, key7 = false;
bool update_flag = false;
bool disp_state = true;
bool blinking = false;
bool dot = false;
unsigned long previousMillis = 0;

void setup() {
    Serial.begin(19200); // Start serial communication at 19200 for debug statements
    Serial.println("TM1650 Buttons Example Code");

    Wire.begin(); // Join the bus as master

    tm1650.init();
    tm1650.setBrightness(bright);
    tm1650.displayChar(0, firstChar, false);
    tm1650.displayChar(1, secondChar, false);
    tm1650.displayChar(2, '-', false);
    tm1650.displayChar(3, dig + '0', false);
}

void loop() {
    byte buttons = tm1650.getButtons();
    unsigned long currentMillis = millis();

    if (blinking) {
        if (currentMillis - previousMillis >= 200) {
            disp_state = !disp_state;
            previousMillis = currentMillis;
            tm1650.displayState(disp_state);
        }
    }

    if (buttons == 0x4f) {
        if (!key1) {
            key1 = true;
            if (firstChar == 'H' and secondChar == 'I') {
              firstChar = 'h';
              secondChar = 'i';
            } else {
              firstChar = 'H';
              secondChar = 'I';
            }
            update_flag = true;
        }
    } else {
        key1 = false;
    }

    if (buttons == 0x47) {
        if (!key2) {
            key2 = true;
            if (!dot) {
                for (int j = 0; j<4; j++) {
                   tm1650.setDot(j,true);
                }
                dot = true;
            } else {
                for (int j = 0; j<4; j++) {
                   tm1650.setDot(j,false);
                }
                dot = false;
            }
        }
    } else {
        key2 = false;
    }
    
    if (buttons == 0x5f) {
        if (!key3) {
            key3 = true;
            if (!blinking) {
                blinking = true;
            } else {
                blinking = false;
                tm1650.displayOn();
                disp_state = true;
            }
        }
    } else {
        key3 = false;
    }

    if (buttons == 0x67) {
        if (!key4) {
            key4 = true;
            if (dig > 0) dig--;
            update_flag = true;
        }
    } else {
        key4 = false;
    }

    if (buttons == 0x6F) {
        if (!key5) {
            key5 = true;
            if (dig < 9) dig++;
            update_flag = true;
        }
    } else {
        key5 = false;
    }

    if (buttons == 0x57) {
        if (!key6) {
            key6 = true;
            bright++;
            if (bright > TM1650_MAX_BRIGHT) {
                bright = TM1650_MIN_BRIGHT;
            }
            tm1650.setBrightness(bright);
        }
    } else {
        key6 = false;
    }
    
    if (buttons == 0x77) {
        if (!key7) {
            key7 = true;
            if (disp_state) {
                tm1650.displayState(false);
                disp_state = false;
            }
            else {
                tm1650.displayState(true);
                disp_state = true;
            }
        }
    } else {
        key7 = false;
    }
    
    if (update_flag) {
        update_flag = false;
        tm1650.displayChar(0, firstChar, false);
        tm1650.displayChar(1, secondChar, false);
        tm1650.displayChar(3, dig + '0', false);
    }

    delay(50);
}
