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
  Serial.begin(576000);
  Serial.setTimeout(1000);
  Serial.println("starting");
  FastLED.addLeds<WS2812B, 17, GRB>(Display.data, Display.height * Display.width);
  FastLED.setBrightness(100);
}
//valid frame = !BF<600bytes>!EF
byte seq_beg[3] = {'!', 'B', 'F'};
byte seq_end[3] = {'!', 'E', 'F'};

byte frame[603];
#define SEQ_LEN 3
#define FRAME_SIZE 600
#define FRAME_SIZE_E (SEQ_LEN + FRAME_SIZE)

void loop()
{
  while (Serial.available() == 0)
  {
  }
  int seq_beg_index = 0;
  while (seq_beg_index < SEQ_LEN)
  { //read a valid header
    byte r = Serial.read();
    if (r == seq_beg[seq_beg_index])
    {
      seq_beg_index++;
    }
  }

  size_t read_len = Serial.readBytes(frame, FRAME_SIZE_E);
  if (read_len != FRAME_SIZE_E)
    return;

  for (int i = 0; i < SEQ_LEN; i++)
    if (frame[FRAME_SIZE + i] != seq_end[i])
      return;

  const int w = 20, h = 20;

  Serial.println("Frame");
  Display.clear();
  int x = 0, y = 0;
  byte c_r, c_g, c_b;
  enum
  {
    CRG,
    CBR,
    CGB
  } state = CRG;
  for (int i = 0; i < FRAME_SIZE_E; i++)
  {
    byte cur_byte = frame[i];
    switch (state)
    {
    case CRG:
      c_r = cur_byte & 0xf0;
      c_g = (cur_byte & 0x0f) << 4;
      state = CBR;
      break;
    case CBR:
      c_b = cur_byte & 0xf0;
      Display.drawPoint(x, y, CRGB(c_r, c_g, c_b));
      c_r = (cur_byte & 0x0f) << 4;
      state = CGB;
      x++;

      break;
    case CGB:
      c_g = cur_byte & 0xf0;
      c_b = (cur_byte & 0x0f) << 4;
      Display.drawPoint(x, y, CRGB(c_r, c_g, c_b));
      state = CRG;
      x++;

      break;
    }
    if (x == 20)
    {
      x = 0;
      y++;
    }
  }

  FastLED.show();
}
