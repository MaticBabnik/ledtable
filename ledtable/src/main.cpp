#include <Arduino.h>
#include <FastLED.h>
#include "graphics2D.h"

StripDisplay disp(11,7);
void demo();
void setup()
{
  Serial.begin(115200);
  Serial.println("waaaad?");
  FastLED.addLeds<WS2812B, 13, GRB>(disp.data, disp.height * disp.width);
  FastLED.setBrightness(10);
  
  FastLED.show();
}

void loop()
{
  demo();
  delay(1000);
}
void demo(){
  disp.clear();
  disp.drawPoint(1, 0, CRGB::Red);
  disp.drawPoint(0, 0, CRGB::Blue);
  disp.drawPoint(0, 1, CRGB::Green);
  FastLED.show();
  delay(500);
  disp.clear();
  FastLED.show();
  delay(400);
  disp.clear(CRGB::Red);
  FastLED.show();
  delay(100);
  disp.drawRect(0,0,10,6,CRGB::Blue);
  disp.drawLine(0,0,10,6,CRGB::Green);
  FastLED.show();
  delay(1000);

}