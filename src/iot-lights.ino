/*
 * Project iot-lights
 * Description:
 * Author:
 * Date:
 */

#include <Particle.h>
#include <neopixel.h>
#include <blynk.h>

#define PIXEL_PIN D2
#define PIXEL_COUNT 150
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
char auth[] = "zFlNo6Xe_5IgrJoBvk8eE8-1XwsDRVKc";

int zergbaFlag = 0;
int brightness;
int r, g, b;

void rainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

void setup() {
    Blynk.begin(auth);

    strip.begin();
    strip.show();
}

void loop() {
    Blynk.run();
    for (int i = 0; i < 150; i++){
        strip.setColorDimmed(i, r, g, b, brightness);
        strip.show();
    }
    
}

BLYNK_WRITE(V0){
    r = param[0].asInt();
    g = param[1].asInt();
    b = param[2].asInt();
}
BLYNK_WRITE(V1){
    int setting = param.asInt();
    if (setting == 1){  //Daylight
        r = 255; g = 255; b = 255;
    }
    if (setting == 2){  //Incandescent
        r = 255; g = 214; b = 170;
    }
    if (setting == 3){  //Candle
        r = 255; g = 147; b = 41;
    }
    while (setting == 4){  //Party
        rainbow(10);
    }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
BLYNK_WRITE(V2){
    brightness = param.asInt();
}