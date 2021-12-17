#include <FastLED.h>

#define NUM_LEDS 440

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
}
void loop() {
  WORD();
  delay(5000);
  FastLED.clear(); // Clear previous setting
  leds[3] = CRGB::White; FastLED.show();
  delay(1000);
}


void WORD()
{
  leds[297] = CRGB::White; FastLED.show();
  leds[298] = CRGB::White; FastLED.show();

  leds[301] = CRGB::White; FastLED.show();
  leds[302] = CRGB::White; FastLED.show();
  
  leds[305] = CRGB::White; FastLED.show();
  leds[306] = CRGB::White; FastLED.show();

  leds[309] = CRGB::White; FastLED.show();
  leds[310] = CRGB::White; FastLED.show();

}
