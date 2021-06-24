#include <FastLED.h>

#define NUM_LEDS 402

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  delay(3500);
}
void loop() {
  // EINS
  FUNF();
  delay(5000);
}

void FUNF()
{
  leds[219] = CRGB::White; FastLED.show();
  //leds[220] = CRGB::White; FastLED.show();
}
