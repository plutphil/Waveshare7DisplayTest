#include "TAMC_GT911.h"

#define TOUCH_SDA  8
#define TOUCH_SCL  9
#define TOUCH_INT 4
#define TOUCH_RST -1 // EXIO 1
#define TOUCH_WIDTH  800
#define TOUCH_HEIGHT 400

TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

void setupTouch() {
  Serial.begin(115200);
  Serial.println("TAMC_GT911 Example: Ready");
  
// #define ESP_LCD_TOUCH_IO_I2C_GT911_ADDRESS          (0x5D)
// #define ESP_LCD_TOUCH_IO_I2C_GT911_ADDRESS_BACKUP   (0x14)
  tp.begin(0x5D);
  tp.setRotation(1);
}

void loopTouch() {
  tp.read();
  if (tp.isTouched){
    for (int i=0; i<tp.touches; i++){
      Serial.print("Touch ");Serial.print(i+1);Serial.print(": ");;
      Serial.print("  x: ");Serial.print(tp.points[i].x);
      Serial.print("  y: ");Serial.print(tp.points[i].y);
      Serial.print("  size: ");Serial.println(tp.points[i].size);
      Serial.println(' ');
      gfx->drawCircle(tp.points[i].x, tp.points[i].y, tp.points[i].size, RGB565_RED);
      gfx->drawLine(tp.points[i].x-tp.points[i].size, tp.points[i].y, tp.points[i].x+tp.points[i].size, tp.points[i].y, RGB565_RED);
      gfx->drawLine(tp.points[i].x, tp.points[i].y-tp.points[i].size, tp.points[i].x, tp.points[i].y+tp.points[i].size, RGB565_RED);
    }
  }
  delay(100);
}