#include <main/main.h>

static uint32_t screenWidth;
static uint32_t screenHeight;
static uint32_t bufSize;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
static lv_color_t *buf1;
static lv_color_t *buf2;

#define BUFFER_SIZE (400 * 960 / 10 * sizeof(lv_color_t))

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
#ifndef DIRECT_MODE
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
Serial.println("LOG 0");
Serial.printf("w: %d, h: %d\n", w, h);
Serial.printf("x1: %d, x2: %d\n", area->x1, area->x2);
Serial.printf("y1: %d, y2: %d\n", area->y1, area->y2);
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif
#endif // #ifndef DIRECT_MODE

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
//hàm đọc giá trị cảm ứng
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void setup(void)
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  while(!Serial);
  
  if (!psramInit()) {
    Serial.println("PSRAM initialization failed!");
  } else {
    Serial.println("PSRAM initialized successfully.");
  }

  #ifdef GFX_EXTRA_PRE_INIT
    GFX_EXTRA_PRE_INIT();
  #endif

  pinMode(GPIO_NUM_42, OUTPUT);
  digitalWrite(GPIO_NUM_42, 0);
  delay(200);
  digitalWrite(GPIO_NUM_42, 1);
  delay(200);

    // Init Display
    if (!gfx->begin())
    {
      Serial.println("gfx->begin() failed!");
    }
    gfx->fillScreen(BLACK);

  #ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
  #endif
    touch_init(gfx->width(), gfx->height(), gfx->getRotation());
    lv_init();

    screenWidth = gfx->width();
    screenHeight = gfx->height();

  #ifdef DIRECT_MODE
    bufSize = screenWidth * screenHeight;
  #else
    bufSize = screenWidth * 40; //screenWidth * 40
  #endif

#ifdef ESP32
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * bufSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_DMA);
  // buf1 = (lv_color_t *)heap_caps_malloc(BUFFER_SIZE, MALLOC_CAP_DMA);
  // buf2 = (lv_color_t *)heap_caps_malloc(BUFFER_SIZE, MALLOC_CAP_DMA);

  buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * bufSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_DMA);
  buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * bufSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_DMA);

  // assert(buf1);
  // assert(buf2);
  if (!disp_draw_buf)
  {
    // remove MALLOC_CAP_INTERNAL flag try again
    //disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * bufSize, MALLOC_CAP_DMA);
    
  }
#else
  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * bufSize);
#endif
    //lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, bufSize);
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, bufSize);
    //lv_disp_draw_buf_init(&draw_buf, buf1, buf2, BUFFER_SIZE / sizeof(lv_color_t));

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
#ifdef DIRECT_MODE
    disp_drv.direct_mode = true;
#endif
    lv_disp_drv_register(&disp_drv);
/* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    //lv_demo_benchmark(); //uncomment this if want to benchmark LCD, #define LV_BENCH_MARK_DEMO in lv_conf.h
    ui_init();
    Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  #ifdef DIRECT_MODE
  #if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(0, 0, (uint16_t *)disp_draw_buf, screenWidth, screenHeight);
  #else
    gfx->draw16bitRGBBitmap(0, 0, (uint16_t *)disp_draw_buf, screenWidth, screenHeight);
  #endif
  #endif // #ifdef DIRECT_MODE

  #ifdef CANVAS
    gfx->flush();
  #endif
  delay(5);
}