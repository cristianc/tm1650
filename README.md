# Update (by cristianc)

Added new example for display boards equipped with seven (instead of three) buttons. I've successfully tested this sketch with JNFD650.DVB168C2.VER1.2 2018/01/25 display board which I've got from a DVB set-top box based on AiP650EO ic (I've also tested the other examples with a display board based on FD650B ic but buttons didn't work).
[![display board - AiP650EO ic](/display_board.png)]

7 segment display driver for JY-MCU module based on TM1650 chip
Copyright (c) 2015 Anatoli Arkhipenko
2018 Alexey Voloshin <microseti@yandex.ru>

Changelog:
	v1.0.0:
		2015-02-24 - Initial release 
 
	v1.0.1:  
		2015-04-27 - Added support of program memery (PROGMEM) to store the ASCII to Segment Code table

	v1.0.2
		2015-08-08 - Added check if panel is connected during init. All calls will be disabled is panel was not connected during init.

	v1.1.0:
		2015-12-20 - Code clean up. Moved to a single header file. Added Gradual brightness method
	
	v1.2.0:
		2018-09-04 - Added buttons support

	v1.3.0:
		2021-06-29 - Fix method getButtons and modification of example02

