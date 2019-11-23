#define NUM_LEDS 18
#define G2D_LEDS_W 20
#define G2D_LEDS_H 20

#include <Arduino.h>
#include <FastLED.h>
#include "graphics2D.h"


CRGB leds[NUM_LEDS];
StripDisplay disp(18,1);

void fillLeds(){
  for(int i=0;i<18;i++){
    disp.data[i] = CRGB(255,127,000);
  }
}

void setup() {
  FastLED.addLeds<WS2813,13,GRB>(disp.data, NUM_LEDS);
  FastLED.setBrightness(50);
  fillLeds();
  FastLED.show();
}

void loop() {
   //put your main code here, to run repeatedly:
  fillLeds();
  FastLED.show();
  delay(30);
}