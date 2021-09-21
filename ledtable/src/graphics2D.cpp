/*
/////////////////////////////////////////////////
! File:         graphics2D.cpp
! Description:  2D graphics for a led strip grid
! Authors:      Matic Babnik
/////////////////////////////////////////////////
*/

#include <Arduino.h>
#include <FastLED.h>
#include "graphics2D.h"

//constructor
StripDisplay::StripDisplay(byte w, byte h)
{
    StripDisplay::width = w;
    StripDisplay::height = h;
    CRGB d[w * h]; //calculate the array size
    StripDisplay::data = d;
}

//Draws one pixel.
void StripDisplay::drawPoint(byte x, byte y, CRGB color)
{
    StripDisplay::data[pointToIndex(x, y)] = color;
}

//Draws the outline of a rectangle.
void StripDisplay::drawRect(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
    StripDisplay::drawLine(x1, y1, x2, y1, color);
    StripDisplay::drawLine(x1, y1, x1, y2, color);
    StripDisplay::drawLine(x2, y1, x2, y2, color);
    StripDisplay::drawLine(x1, y2, x2, y2, color);
}

//fils a rectangle
void StripDisplay::fillRect(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
    if (y2 > y1)
    {
        for (int i = y1; i <= y2; i++)
        {
            StripDisplay::drawLine(x1, i, x2, i, color);
        }
    }
    else
    {
        for (int i = y1; i >= y2; i--)
        {
            StripDisplay::drawLine(x1, i, x2, i, color);
        }
    }
}

//Draws a line from point 1 to point 2.
void StripDisplay::drawLine(byte x1, byte y1, byte x2, byte y2, CRGB color)
{
    if (x1 == x2) //horizontal line
    {
        if (y1 > y2)
        {
            for (int y = y1; y >= y2; y--)
            {
                StripDisplay::data[pointToIndex(x1, y)] = color;
            }
        }
        if (y1 < y2)
        {
            for (int y = y1; y <= y2; y++)
            {
                StripDisplay::data[pointToIndex(x1, y)] = color;
            }
        }
    }
    else if (y1 == y2) //vertical line
    {
        if (x1 > x2)
        {
            for (int x = x1; x >= x2; x--)
            {
                StripDisplay::data[pointToIndex(x1, y1)] = color;
            }
        }
        if (x1 < x2)
        {
            for (int x = x1; x <= x2; x++)
            {
                StripDisplay::data[pointToIndex(x, y1)] = color;
            }
        }
    }
    else //diagonal line
    {
        int xdiff = x2 - x1, ydiff = y2 - y1; //relative x and y changes
        float x = x1, y = y1;                 //set current position to first point
        uint8_t cycles;
        if (abs(xdiff) == abs(ydiff)) //set cycles to larger change (and make it positive)
        {
            cycles = abs(xdiff);
        }
        else if (abs(xdiff) > abs(ydiff))
        {
            cycles = abs(xdiff);
        }
        else
        {
            cycles = abs(ydiff);
        }
        for (byte i = 0; i <= cycles; i++)
        {
            StripDisplay::data[StripDisplay::pointToIndex(roundf(x), roundf(y))] = color; //draw pixel at rounded position
            x += (float)xdiff / cycles;                                                   //move 1/cycles towards the 2nd point
            y += (float)ydiff / cycles;
        }
    }
}

//Converts 2D coordinates into 1D snake strip
int StripDisplay::pointToIndex(byte x, byte y)
{
    if (y % 2 == 1) //check if the pixels in the column are in the right or wrong order
    {
        return y * StripDisplay::width + x;
    }
    else
    {
        return y * StripDisplay::width + StripDisplay::width - 1 - x;
    }
}

//Clears the strip/display
void StripDisplay::clear()
{
    for (int i = 0; i < StripDisplay::height * StripDisplay::width; i++)
    {
        StripDisplay::data[i] = CRGB::Black;
    }
}

//Fills the strip/display with a selected color
void StripDisplay::clear(CRGB color)
{
    for (int i = 0; i < StripDisplay::height * StripDisplay::width; i++)
    {
        StripDisplay::data[i] = color;
    }
}

//function to test the library/mcu/display
void StripDisplay::demo()
{
    StripDisplay::clear();
    StripDisplay::drawPoint(1, 0, CRGB::Red);
    StripDisplay::drawPoint(0, 0, CRGB::Blue);
    StripDisplay::drawPoint(0, 1, CRGB::Green);
    FastLED.show();
    delay(1000);
    StripDisplay::clear();
    FastLED.show();
    delay(1000);
    StripDisplay::clear(CRGB::Red);
    FastLED.show();
    delay(1000);
    StripDisplay::drawRect(0, 0, StripDisplay::width - 1, StripDisplay::height - 1, CRGB::Blue);
    StripDisplay::drawLine(0, 0, StripDisplay::width - 1, StripDisplay::height - 1, CRGB::Green);
    FastLED.show();
    delay(1000);
}
