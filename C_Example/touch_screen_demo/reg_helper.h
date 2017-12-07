#include <avr/io.h>

#include "config.h"

/* This file is configured for Arduino Uno only
 * */
// LCD control lines:
// RD (read), WR (write), CD (command/data), CS (chip select)
#define RD_PORT     PORTC
#define WR_PORT     PORTC
#define CD_PORT     PORTC
#define CS_PORT     PORTC
#define RESET_PORT  PORTC

#define RD_PIN      PC0				    /*pin A0 */
#define WR_PIN      PC1				    /*pin A1 */
#define CD_PIN      PC2				    /*pin A2 */
#define CS_PIN      PC3				    /*pin A3 */
#define RESET_PIN   PC4                 /*pin A4 */

// Touch detector lines
#define YP_PIN 		PC3  	// must be an analog
#define XM_PIN 		PC2  	// must be an analog
#define YM_PIN 		PB1   	// can be a digital pin
#define XP_PIN 		PB0   	// can be a digital pin

#define YP_PORT		PORTC
#define XM_PORT		PORTC
#define YM_PORT		PORTB
#define XP_PORT		PORTB

#define YP_SET_INPUT()	{ DDRC &= ~(1 << YP_PIN);}
#define YP_SET_OUTPUT()	{ DDRC |= 1 << YP_PIN;}
#define YP_SET_LOW()	{ YP_PORT &= ~(1 << YP_PIN);}
#define YP_SET_HIGH()	{ YP_PORT |= 1 << YP_PIN;}

#define XM_SET_INPUT()	{ DDRC &= ~(1 << XM_PIN);}
#define XM_SET_OUTPUT()	{ DDRC |= (1 << XM_PIN);}
#define XM_SET_LOW()	{ XM_PORT &= ~(1 << XM_PIN);}
#define XM_SET_HIGH()	{ XM_PORT |= 1 << XM_PIN;}

#define YM_SET_INPUT()	{ DDRB &= ~(1 << YM_PIN);}
#define YM_SET_OUTPUT()	{ DDRB |= 1 << YM_PIN;}
#define YM_SET_LOW()	{ YM_PORT &= ~(1 << YM_PIN);}
#define YM_SET_HIGH()	{ YM_PORT |= 1 << YM_PIN;}

#define XP_SET_INPUT()	{ DDRB &= ~(1 << XP_PIN);}
#define XP_SET_OUTPUT()	{ DDRB |= (1 << XP_PIN);}
#define XP_SET_LOW()	{ XP_PORT &= ~(1 << XP_PIN);}
#define XP_SET_HIGH()	{ XP_PORT |= 1 << XP_PIN;}

#define DMASK         0x03
#define NMASK         ~DMASK
#define write_8(x)    { PORTB = (PORTB & NMASK) | ((x) & DMASK); PORTD = (PORTD & DMASK) | ((x) & NMASK); }
#define read_8()      ( (PINB & DMASK) | (PIND & NMASK) )
#define setWriteDir() { DDRB = (DDRB & NMASK) | DMASK; DDRD = (DDRD & DMASK) | NMASK;  }

#define setReadDir()  { DDRB = (DDRB & NMASK) & NMASK; DDRD = (DDRD & DMASK) & DMASK;  }
#define write8(x)     { write_8(x); WR_STROBE(); }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE(); dst = read_8(); RD_IDLE(); }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))


#define RD_ACTIVE()  PIN_LOW(RD_PORT, RD_PIN)
#define RD_IDLE()    PIN_HIGH(RD_PORT, RD_PIN)
#define RD_OUTPUT()  PIN_OUTPUT(RD_PORT, RD_PIN)
#define WR_ACTIVE()  PIN_LOW(WR_PORT, WR_PIN)
#define WR_IDLE()    PIN_HIGH(WR_PORT, WR_PIN)
#define WR_OUTPUT()  PIN_OUTPUT(WR_PORT, WR_PIN)
#define CD_COMMAND() PIN_LOW(CD_PORT, CD_PIN)
#define CD_DATA()    PIN_HIGH(CD_PORT, CD_PIN)
#define CD_OUTPUT()  PIN_OUTPUT(CD_PORT, CD_PIN)
#define CS_ACTIVE()  PIN_LOW(CS_PORT, CS_PIN)
#define CS_IDLE()    PIN_HIGH(CS_PORT, CS_PIN)
#define CS_OUTPUT()  PIN_OUTPUT(CS_PORT, CS_PIN)
#define RESET_ACTIVE()  PIN_LOW(RESET_PORT, RESET_PIN)
#define RESET_IDLE()    PIN_HIGH(RESET_PORT, RESET_PIN)
#define RESET_OUTPUT()  PIN_OUTPUT(RESET_PORT, RESET_PIN)

 // General macros.   IOCLR registers are 1 cycle when optimised.
#define WR_STROBE() { WR_ACTIVE(); WR_IDLE(); }       //PWLW=TWRL=50ns
#define RD_STROBE() {RD_IDLE(); RD_ACTIVE(); RD_ACTIVE(); RD_ACTIVE();}      //PWLR=TRDL=150ns, tDDR=100ns

#define CTL_INIT()   { RD_OUTPUT(); WR_OUTPUT(); CD_OUTPUT(); CS_OUTPUT(); RESET_OUTPUT(); }
#define WriteCmd(x)  { CD_COMMAND(); write16(x); }
#define WriteData(x) { CD_DATA(); write16(x); }
