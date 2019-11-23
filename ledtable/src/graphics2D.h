#pragma once
#include <Arduino.h>
#include <FastLED.h>
/*
! 2D graphics for a led strip grid

TODO add functions for drawing rectangles, lines and filled rectangles
*/

class StripDisplay
{
private:

public:
    StripDisplay(byte w, byte h);
    CRGB *data;
    byte width;
    byte height;
    void drawPoint(byte x, byte y, CRGB color);
    void drawRect(byte x1, byte y1, byte x2, byte y2, CRGB color);
    void fillRect(byte x1, byte y1, byte x2, byte y2, CRGB color);
    void drawLine(byte x1, byte y1, byte x2, byte y2, CRGB color);
    int PointToIndex(byte x, byte y);
};
