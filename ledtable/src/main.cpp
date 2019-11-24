#include <Arduino.h>
#include <FastLED.h>
#include "graphics2D.h"

StripDisplay Display(11,7);
void setup()
{
  FastLED.addLeds<WS2812B, 13, GRB>(Display.data, Display.height * Display.width);
  FastLED.setBrightness(10);
}

void loop()
{
  Display.demo();
  delay(1000);
}

