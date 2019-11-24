/*
/////////////////////////////////////////////////
! File:         graphics2D.cpp
! Description:  2D graphics for a led strip grid
! Authors:      Matic Babnik
/////////////////////////////////////////////////
TODO fillrect
TODO fix diagonal lines
TODO cleanup
*/

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

//
void StripDisplay::drawPoint(byte x, byte y, CRGB color)
{
    StripDisplay::data[PointToIndex(x, y)] = color;
}

void StripDisplay::drawRect(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
    StripDisplay::drawLine(x1, y1, x2, y1, color);
    StripDisplay::drawLine(x1, y1, x1, y2, color);
    StripDisplay::drawLine(x2, y1, x2, y2, color);
    StripDisplay::drawLine(x1, y2, x2, y2, color);
}

void StripDisplay::fillRect(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
}

void StripDisplay::drawLine(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
    Serial.println("horizontal line");
    if (x1 == x2) //horizontal line
    {
        if (y1 > y2)
        {
            for (int y = y1; y >= y2; y--)
            {
                //Serial.println("Point @ X:" + String(x1) + ",Y:" + String(y));
                StripDisplay::data[PointToIndex(x1, y)] = color;
            }
        }
        if (y1 < y2)
        {
            for (int y = y1; y <= y2; y++)
            {
                //Serial.println("Point @ X:" + String(x1) + ",Y:" + String(y));
                StripDisplay::data[PointToIndex(x1, y)] = color;
            }
        }
    }
    else if (y1 == y2) //vertical line
    {
        Serial.println("vertical line");
        if (x1 > x2)
        {
            for (int x = x1; x >= x2; x--)
            {
                //Serial.println("Point @ X:" + String(x) + ",Y:" + String(y1));
                StripDisplay::data[PointToIndex(x1, y1)] = color;
            }
        }
        if (x1 < x2)
        {
            for (int x = x1; x <= x2; x++)
            {
                //Serial.println("Point @ X:" + String(x) + ",Y:" + String(y1));
                StripDisplay::data[PointToIndex(x, y1)] = color;
            }
        }
    }
    else //diagonal line
    {
        Serial.println("diagonal line");
        uint8_t xdiff = x1 - x2, ydiff = y1 - y2;
        float x = x1, y = y1;
        uint8_t cycles;
        if (abs(xdiff) == abs(ydiff)) //angle is 45
        {
            cycles = abs(xdiff);
            Serial.println("[drawLine] xdiff==ydiff");
        }
        else if (abs(xdiff) > abs(ydiff))
        {
            cycles = abs(xdiff);
            Serial.println("[drawLine] xdiff>ydiff");
        }
        else
        {
            cycles = abs(ydiff);
            Serial.println("[drawLine] xdiff<ydiff");
        }
        for (uint8_t i = 0; i <= cycles; i++)
        {
            StripDisplay::data[StripDisplay::PointToIndex(roundf(x), roundf(y))] = color;
            x += (float)xdiff / cycles;
            y += (float)ydiff / cycles;
        }
    }
}

int StripDisplay::PointToIndex(byte x, byte y)
{
    if (y % 2 == 0)
    {
        //Serial.println("Normal section @ Y:" + String(y));
        return y * StripDisplay::width + x;
    }
    else
    {
        //Serial.println("Reverse section @ Y:" + String(y));
        return y * StripDisplay::width + StripDisplay::width - 1 - x;
    }
}

void StripDisplay::clear()
{
    for (int i = 0; i < StripDisplay::height * StripDisplay::width; i++)
    {
        StripDisplay::data[i] = CRGB::Black;
    }
}

void StripDisplay::clear(CRGB color)
{
    for (int i = 0; i < StripDisplay::height * StripDisplay::width; i++)
    {
        StripDisplay::data[i] = color;
    }
}
