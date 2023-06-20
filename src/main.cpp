#include <Arduino.h>

#include "rm67162.h"
#include "lvgl.h"

#include "ui.h"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf;

void my_disp_flush(lv_disp_drv_t *disp,
                   const lv_area_t *area,
                   lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  lcd_PushColors(area->x1, area->y1, w, h, (uint16_t *)&color_p->full);
  lv_disp_flush_ready(disp);
}

void setup()
{
  // Serial.begin(115200);
  // Serial.println("T-DISPLAY-S3-AMOLED FACTORY TEST");
  // pinMode(PIN_BAT_VOLT, ANALOG);

  rm67162_init(); // amoled lcd initialization
  lcd_setRotation(1);

  delay(1000);

  lv_init();


  buf = (lv_color_t *)ps_malloc(sizeof(lv_color_t) * LVGL_LCD_BUF_SIZE);
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, LVGL_LCD_BUF_SIZE);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = EXAMPLE_LCD_H_RES;
  disp_drv.ver_res = EXAMPLE_LCD_V_RES;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  ui_init();
}

void loop()
{
  lv_timer_handler();
  delay(2);
}
