#ifndef _HW_CFG_
#define _HW_CFG_

/* Configure your TFTLCD screen here */
#define DRIVER_ID 	9341
#define TFTWIDTH   	240
#define TFTHEIGHT  	320

/* Touch digitizer configuration */
#define TS_MINX 100
#define TS_MAXX 920
#define TS_MINY 70
#define TS_MAXY 900

/* Comment out optional graphical components if not needed (Saves up to 2568 bytes)
 * */
#define SUPPORT_READ_PIXEL
#define SUPPORT_VERT_SCROLL
#define SUPPORT_CHECKBOX
#define SUPPORT_RADIO_BUTTON
#define SUPPORT_LED
#define SUPPORT_BUTTON

#endif  //_HW_CFG_

