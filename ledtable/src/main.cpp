#include <Arduino.h>
#include <FastLED.h>
#include "graphics2D.h"

//
//#define VIRTUAL_STRIP
#define DEBUG_SERIAL_PORT Serial

#include "debug.h"

StripDisplay Display(20, 20);

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(1000);
  Serial.println("starting");
  FastLED.addLeds<WS2812B, 17, GRB>(Display.data, Display.height * Display.width);
  FastLED.setBrightness(100);
}
//valid frame = !FR<50bytes>!EF
byte seq_beg[3] = {'!', 'F', 'R'};
byte seq_end[3] = {'!', 'E', 'F'};

byte frame[53];

void loop()
{
  while (Serial.available() == 0)
  {
  }
  int seq_beg_index = 0;
  while (seq_beg_index < 3)
  { //read a valid header
    byte r = Serial.read();
    if (r == seq_beg[seq_beg_index])
    {
      seq_beg_index++;
    }
  }

  size_t read_len = Serial.readBytes(frame, 53);
  if (read_len != 53)
    return;

  for (int i = 0; i < 3; i++)
    if (frame[50 + i] != seq_end[i])
      return;

  const int w = 20, h = 20;
  int x = 0, y = 0;
  
  Serial.println("Frame");
  Display.clear();
  for (int i = 0; i < 50; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      byte cur = 0b10000000 & (frame[i] << j);
      Display.drawPoint(x, y, cur > 0 ? CRGB::White : CRGB::Black);
      x++;
      if (x == 20)
      {
        x = 0;
        y++;
      }
    }
  }
  FastLED.show();
}
