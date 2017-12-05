/*
 * main.c
 *
 *  Created on: Dec 1, 2017
 *      Author: ujagaga
 */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include "HW_config.h"
#include "GFX.h"
#include "uart.h"
#include "TouchScreen.h"


#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK        0xF81F

#define DEBOUNCE_THRESHOLD	500

int main( void )
{
	DDRB = 1;
	uart_init();

	uart_printStr("Starting LCD test");
	uart_printStr("\n\rLCD ID: ");

	uint16_t ID = GFX_init();
	uart_printHex(ID);

	uart_printStr("\n\rTFT size is ");
	uart_printDec(GFX_getWidth());
	uart_printStr(" x ");
	uart_printDec(GFX_getHeight());


	while(1){
		GFX_fillScreen(BLACK);
		GFX_setCursor(0, 0);

		GFX_setTextColor(RED, RED);
		GFX_setTextSize(1);
		GFX_printStr("Hello World!\n");
		GFX_printDec(12345);
		GFX_printDec(6789);
		GFX_printStr("\n");
		GFX_printHex(0xDEAD);
		GFX_printHex(0xBEEF);
		GFX_printStr("\n");

		GFX_setTextColor(GREEN, GREEN);
		GFX_setTextSize(2);
		GFX_printStr("Hello World!\n");
		GFX_printDec(12345);
		GFX_printDec(6789);
		GFX_printStr("\n");
		GFX_printHex(0xDEAD);
		GFX_printHex(0xBEEF);
		GFX_printStr("\n");

		GFX_setTextColor(WHITE, WHITE);
		GFX_setTextSize(4);
		GFX_printStr("\nHello!\n");

		GFX_setTextColor(YELLOW, YELLOW);
		GFX_setTextSize(5);
		GFX_printStr("Hello!\n");

		GFX_setTextColor(RED, RED);
		GFX_setTextSize(6);
		GFX_printStr("Hello!\n");

		GFX_setTextColor(BLUE, BLUE);
		GFX_setTextSize(3);
		GFX_printStr("Display ID:\n");
		GFX_printStr("ILI");
		GFX_printHex(ID);

		_delay_ms(2000);

		GFX_fillRect(20, 20, 200, 280, BLACK);
		GFX_drawRect(20, 20, 200, 280, RED);
		GFX_drawLine(20, 20, 200, 300, BLUE);
		GFX_drawCircle(50, 50, 20, GREEN);
		GFX_fillCircle(100, 100, 50, CYAN);
		GFX_drawTriangle(100, 200, 100, 270, 200, 240, MAGENTA);
		GFX_fillTriangle(120, 220, 120, 250, 180, 240, YELLOW);
		GFX_fillRect(60, 200, 30, 20, MAGENTA);

		_delay_ms(2000);

		GFX_fillRect(40, 40, 160, 240, BLACK);
		GFX_drawRect(40, 40, 160, 240, GREEN);

		char btn1_label[] = "Button";
		gfx_btn btn1;

		btn1.fillcolor = BLUE;
		btn1.height = 30;
		btn1.label = btn1_label;
		btn1.outlinecolor = WHITE;
		btn1.textcolor = BLACK;
		btn1.textsize = 2;
		btn1.width = 120;
		btn1.x = 110;
		btn1.y = 70;

		/* example of a normally displayed button */
		GFX_btnDraw(&btn1, false);

		btn1.y = 120;

		/* example of an inverted (pressed) button */
		GFX_btnDraw(&btn1, true);

		gfx_chkbox chk1;

		chk1.color = OLIVE;
		chk1.fillcolor = BLACK;
		chk1.width = 30;
		chk1.x = 80;
		chk1.y = 160;
		chk1.checked = true;

		GFX_chkBoxDraw(&chk1);

		_delay_ms(2000);

		GFX_setTextColor(OLIVE, OLIVE);
		GFX_setTextSize(2);
		GFX_setCursor(chk1.x + chk1.width/2 + TXTW , chk1.y - TXTH);

		GFX_printStr("Try me");

		char btn2_label[] = "Continue";
		gfx_btn btn2;

		btn2.fillcolor = ORANGE;
		btn2.height = 30;
		btn2.label = btn2_label;
		btn2.outlinecolor = WHITE;
		btn2.textcolor = BLACK;
		btn2.textsize = 2;
		btn2.width = 120;
		btn2.x = 150;
		btn2.y = 250;

		GFX_btnDraw(&btn2, false);

		TSPoint point;

		uart_printStr("\n\r\n\n");
		while(1){

			TS_getPoint(&point);

			if(point.z > 0){
				uart_printStr("\rx:");
				uart_printDec(point.x);
				uart_printStr(", y:");
				uart_printDec(point.y);
				uart_printStr(", press:");
				uart_printDec(point.z);
				uart_printStr("    ");
			}

			GFX_btnUpdate(&btn2, &point);
			GFX_chkBoxUpdate(&chk1, &point);

			if(GFX_btnJustReleased(&btn2)){
				uart_printStr("\n\r Released\n\r");
				break;
			}

			if(GFX_btnJustPressed(&btn2)){
				uart_printStr("\n\r Pressed\n\r");
			}
		}
	}

	return 0;
}
