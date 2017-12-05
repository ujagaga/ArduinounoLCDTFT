#ifndef _GFX_H
#define _GFX_H

#include <stdbool.h>
#include <stdint.h>
#include "HW_config.h"

#if DRIVER_ID==9341
	#include "LCD_ILI9341.h"
#else
#error Curently only driver ID 9341 is supported
#endif

#define CORNER_NW	(0b0001)
#define CORNER_NE	(0b0010)
#define CORNER_SE	(0b0100)
#define CORNER_SW	(0b1000)


typedef struct gfx_btn_t{
	int16_t x;
	int16_t y;
	uint16_t outlinecolor;
	uint16_t fillcolor;
	uint16_t textcolor;
	uint8_t width;
	uint8_t height;
	uint8_t textsize;
	volatile uint8_t debounce;
	bool currstate;
	bool laststate;
	char *label;
}gfx_btn;

typedef struct gfx_chkbox_t{
	int16_t x;
	int16_t y;
	uint16_t color;
	uint8_t width;
	bool checked;
}gfx_chkbox;

extern int16_t GFX_getHeight(void);
extern int16_t GFX_getWidth(void);
extern void GFX_setHeight(int16_t h);
extern void GFX_setWidth(int16_t w);
extern void GFX_setRotation(uint8_t r);
extern uint8_t GFX_getRotation(void);
extern uint16_t GFX_init( void );		// returns display ID
extern void GFX_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
extern void GFX_fillScreen(uint16_t color);
extern void GFX_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
extern void GFX_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
extern void GFX_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
extern void GFX_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
extern void GFX_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
extern void GFX_drawRoundCorner(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
extern void GFX_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
extern void GFX_fillRoundCorner(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
extern void GFX_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
extern void GFX_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
extern void GFX_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
extern void GFX_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
extern void GFX_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
extern void GFX_setTextColor(uint16_t c, uint16_t b);
extern void GFX_setTextSize(uint8_t s);
extern void GFX_setTextWrap(bool w);
extern void GFX_setCursor(int16_t x, int16_t y);
extern void GFX_printStr(char *string);
extern void GFX_printDec(uint16_t number);
extern void GFX_printHex(uint16_t number);
extern int16_t GFX_getCursorX(void);
extern int16_t GFX_getCursorY(void);
extern void GFX_cp437(bool x);
extern void GFX_btnDraw(gfx_btn *btn, bool inverted);
extern bool GFX_btnContains(gfx_btn *btn, int16_t x, int16_t y);
extern void GFX_chkBoxDraw(gfx_chkbox *chk, bool checked);
extern bool GFX_chkBoxContains(gfx_chkbox *chk, int16_t x, int16_t y);
extern void GFX_btnPress(gfx_btn *btn, bool p);
extern bool GFX_btnIsPressed(gfx_btn *btn);
extern bool GFX_btnJustReleased(gfx_btn *btn);

/* Check out LCD_ILI9341.h */
#ifdef SUPPORT_VERT_SCROLL
extern void GFX_vertScroll(int16_t top, int16_t scrollines, int16_t offset);
#endif


#endif // _ADAFRUIT_GFX_H
