#include <Arduino.h>
#include <FastLED.h>
#include "graphics2D.h"

//
#define VIRTUAL_STRIP
#define DEBUG_SERIAL_PORT Serial

#include "debug.h"

StripDisplay Display(20,20);

void setup()
{
  Serial.begin(115200);
  Serial.println("starting");
  FastLED.addLeds<WS2812B, 13, GRB>(Display.data, Display.height * Display.width);
  FastLED.setBrightness(10);
}

void loop()
{
  Display.clear();
  Display.drawLine(0,0,19,19,CRGB::Amethyst);
  StripDebug(Display.data,Display.height*Display.width);
  delay(100);
  Display.clear(CRGB::Aqua);
  delay(100);
  StripDebug(Display.data,Display.height*Display.width);
}

