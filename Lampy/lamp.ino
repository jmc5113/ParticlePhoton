// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

Adafruit_NeoPixel Pixy1(1, D1, WS2811);

void setup() {
    Pixy1.begin();
    Pixy1.setPixelColor(0, 0x00, 0x00, 0xff);
    Pixy1.show();

}

void loop() {

}