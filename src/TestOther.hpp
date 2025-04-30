#include <CH422G.hpp>
CH422G ch422;

#define TP_RST 1      // Touch screen reset pin
#define LCD_BL 2      // LCD backlight pinout
#define LCD_RST 3     // LCD reset pin
#define SD_CS 4       // SD card select pin
#define USB_SEL 5     // USB select pin
#define LCD_VDD_EN 6
void setup2() {
    Wire.begin(8,9);
    ch422.begin();

    ch422.pinMode(TP_RST, OUTPUT);
    ch422.digitalWrite(TP_RST, HIGH);

    ch422.pinMode(LCD_BL, OUTPUT);
    ch422.digitalWrite(LCD_BL, HIGH);

    ch422.pinMode(LCD_RST, OUTPUT);
    ch422.digitalWrite(LCD_RST, HIGH);

    ch422.pinMode(SD_CS, OUTPUT);
    ch422.digitalWrite(SD_CS, HIGH);

    ch422.pinMode(USB_SEL, OUTPUT);
    ch422.digitalWrite(USB_SEL, HIGH);

}

