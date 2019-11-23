#include <Arduino.h>
#include <FastLED.h>
#include "graphics2D.h"

StripDisplay::StripDisplay(byte w, byte h)
{
    StripDisplay::width = w;
    StripDisplay::height = h;
    CRGB d[w * h];
    StripDisplay::data = d;
}

/*
void StripDisplay::drawPoint(byte x, byte y, CRGB color)
{
}
void StripDisplay::drawRect(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
}
void StripDisplay::fillRect(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
}
void StripDisplay::drawLine(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
}
int StripDisplay::PointToIndex(byte x, byte y)
{
    if (y % 2 == 0)
        return y * StripDisplay::width + x;
    else
    {
        return y * StripDisplay::width + StripDisplay::height - 1 - x;
    }
}
*/