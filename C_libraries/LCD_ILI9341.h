#ifndef MCUFRIEND_KBV_H_
#define MCUFRIEND_KBV_H_

#include <stdint.h>
#include <stdbool.h>

extern void TFTLCD_begin();
extern void TFTLCD_reset(void);
extern uint16_t TFTLCD_readID(void);
extern void TFTLCD_drawPixel(int16_t x, int16_t y, uint16_t color);
extern void TFTLCD_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
extern void TFTLCD_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
extern void TFTLCD_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
extern void TFTLCD_setRotation(uint8_t r);


/* Optional. Adds 158 bytes to code */
//#define SUPPORT_READ_PIXEL
#ifdef SUPPORT_READ_PIXEL
extern uint16_t TFTLCD_readPixel(int16_t x, int16_t y);
#else
#define TFTLCD_readPixel(x, y)
#endif

/* Optional. Adds 194 bytes to code */
//#define SUPPORT_VERT_SCROLL
#ifdef SUPPORT_VERT_SCROLL
extern void TFTLCD_vertScroll(int16_t top, int16_t scrollines, int16_t offset);
#else
#define TFTLCD_vertScroll(top, scrollines, offset)
#endif

#endif
