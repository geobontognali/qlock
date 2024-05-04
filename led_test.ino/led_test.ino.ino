#include <FastLED.h>

#define NUM_LEDS 545

CRGB leds[NUM_LEDS];
int i = 0;
void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
}
void loop() {
  i = i + 2;
  leds[i] = CRGB::Red; FastLED.show();
  delay(25);
  FastLED.clear(); // Clear previous setting
}

