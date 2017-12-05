// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#ifndef _TOUCHSCREEN_H_
#define _TOUCHSCREEN_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct TSPoint_t{
	int16_t x;
	int16_t y;
	int16_t z;
}TSPoint;

extern void TS_getPoint(TSPoint *result);

#endif
