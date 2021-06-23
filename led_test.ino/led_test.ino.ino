#include <FastLED.h>

#define NUM_LEDS 402

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  delay(5000);
}
void loop() {

  /*
    for(int i = 0; i <= 401; i++)
    {
    leds[i] = CRGB::White; FastLED.show();
    delay(5);
    leds[i] = CRGB::Black; FastLED.show();
    }
  */
  FastLED.clear();

  leds[370] = CRGB::Black; FastLED.show();

  delay(2000);
  FastLED.clear();
  // ES IST
  leds[0] = CRGB::White; FastLED.show();
  leds[1] = CRGB::White; FastLED.show();
  leds[2] = CRGB::White; FastLED.show();

  leds[4] = CRGB::White; FastLED.show();
  leds[5] = CRGB::White; FastLED.show();


  leds[12] = CRGB::White; FastLED.show();
  leds[13] = CRGB::White; FastLED.show();

  leds[16] = CRGB::White; FastLED.show();
  leds[17] = CRGB::White; FastLED.show();

  leds[20] = CRGB::White; FastLED.show();
  leds[21] = CRGB::White; FastLED.show();


  // EINS
  leds[251] = CRGB::White; FastLED.show();
  leds[252] = CRGB::White; FastLED.show();

  leds[255] = CRGB::White; FastLED.show();
  leds[256] = CRGB::White; FastLED.show();

  leds[259] = CRGB::White; FastLED.show();
  leds[260] = CRGB::White; FastLED.show();

  leds[263] = CRGB::White; FastLED.show();
  leds[264] = CRGB::White; FastLED.show();
  delay(5000);
}
