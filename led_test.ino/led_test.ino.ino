#include <FastLED.h>

#define NUM_LEDS 445

CRGB leds[NUM_LEDS];
int i = 0;
void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
}
void loop() {
  i = i + 1;
  leds[i] = CRGB::White; FastLED.show();
  delay(50);
  FastLED.clear(); // Clear previous setting
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
