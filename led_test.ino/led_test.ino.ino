#include <FastLED.h>

#define NUM_LEDS 445

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
  leds[444] = CRGB::White; FastLED.show();
  leds[443] = CRGB::White; FastLED.show();

  leds[440] = CRGB::White; FastLED.show();
  leds[439] = CRGB::White; FastLED.show();
  
  leds[436] = CRGB::White; FastLED.show();
  leds[435] = CRGB::White; FastLED.show();

  leds[432] = CRGB::White; FastLED.show();
  leds[431] = CRGB::White; FastLED.show();
}
