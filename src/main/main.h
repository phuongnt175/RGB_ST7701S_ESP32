#include <Arduino_GFX_Library.h>
#include <Arduino.h>
#include <lvgl.h>
#include <ui.h>
#include <Touch/touch.h>
#include <benchmark/lv_demo_benchmark.h>

#define GFX_BL GPIO_NUM_3 // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

Arduino_DataBus *bus = new Arduino_SWSPI(GFX_NOT_DEFINED /*DC*/, 7 /*CS*/, 6 /*SCK*/, 5 /*MOSI*/, GFX_NOT_DEFINED /*MISO*/);

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    9 /*DE*/, 10 /*VSYNC*/, 11 /*HSYNC*/, 8 /*PCLK */,
    17 /* R0 */, 2 /* R1 */, 1 /* R2 */, 46 /* R3 */,  38 /* R4 */,
    18 /* G0 */, 19 /* G1 */, 20 /* G2 */, 21 /* G3 */, 48 /* G4 */, 47 /* G5 */,
    12 /* B0 */, 13 /* B1 */, 14 /* B2 */, 15 /* B3 */, 16 /* B4 */,
    1 /* hsync_polarity */, 40 /* hsync_front_porch */, 12 /* hsync_pulse_width */, 60 /* hsync_back_porch */,
    1 /* vsync_polarity */, 20 /* vsync_front_porch */, 6 /* vsync_pulse_width */, 10 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 16000000 /* prefer_speed */, false /*useBigEndian*/,
    0 /*de_idle_high*/, 1 /*pclk_idle_high*/);

Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
400 /* width */, 960 /* height */, rgbpanel, 0 /* rotation */, true /*auto_flush */,
bus, 4 /*38 RST */, st7701_type9_init_operations, sizeof(st7701_type9_init_operations));