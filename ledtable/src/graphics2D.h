/*
/////////////////////////////////////////////////
! File:         graphics2D.h
! Description:  2D graphics for a led strip grid
! Authors:      Matic Babnik
/////////////////////////////////////////////////
*/

#pragma once
#include <Arduino.h>
#include <FastLED.h>

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
    void clear();
    void clear(CRGB color);
    int PointToIndex(byte x, byte y);
};
