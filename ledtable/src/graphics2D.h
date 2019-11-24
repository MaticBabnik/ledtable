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
    CRGB *data;
    byte width;
    byte height;

    StripDisplay(byte w, byte h);

    int  pointToIndex(byte x, byte y);
    void drawPoint(byte x, byte y, CRGB color);
    void drawRect(byte x1, byte y1, byte x2, byte y2, CRGB color);
    void fillRect(byte x1, byte y1, byte x2, byte y2, CRGB color);
    void drawLine(byte x1, byte y1, byte x2, byte y2, CRGB color);
    void clear();
    void clear(CRGB color);
    void demo();
};
