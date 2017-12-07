# ArduinounoLCDTFT

I bought a 2,8inch LCDTFT from Aliexpress along with an Arduino UNO clone. 
I do not like using Arduino studio because I prefer to optimize the code size and C++ is just not optimized enough.
This is why I re-wrote the TFTLCD libraries from C++ to pure C and saved almost 10KB of flash. 

I am using only Arduino Uno and a display with ILI9341 chip, so I removed all other support to make the code simpler 
and smaller. If I start using another display, I will add support for it based on existing C++ libraries.
If you are not sure which LCD driver your screen uses, just try the code and open serial therminal. 
The first thing displayed via UART (baud 9600) is the LCD driver ID.
I have also improoved the button debouncing significantly.

This repo contains the original Adafruit and MCUFRIEND TFTLCD libraries and examples, 
my optimized pure C libraries and a touch_screen_demo eclipse example.

Feel free to use as you wish.

NOTE: 
1. configure the pins used in the reg_helper.c 
2. configure graphic library functions in config.h (also checkout GFX.h for function reference)