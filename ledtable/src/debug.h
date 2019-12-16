/*
/////////////////////////////////////////////////
! File:         debug.h
! Description:  Simulate displays over serial.
! Authors:      Matic Babnik
/////////////////////////////////////////////////
*/

#pragma once
#include <Arduino.h>
#include <FastLED.h>

#ifndef DEBUG_SERIAL_PORT
#define DEBUG_SERIAL_PORT Serial
#endif


void StripDebug(CRGB* data, uint length)
{
    #ifdef VIRTUAL_STRIP
    DEBUG_SERIAL_PORT.print("MSG>");

    int sred, sgreen, sblue;

    for (uint i = 0;i<length;i++){
        sred = data[i].red / 16;
        sgreen = data[i].green / 16;
        sblue = data[i].blue / 16;
        
        DEBUG_SERIAL_PORT.print(sred,16);
        DEBUG_SERIAL_PORT.print(sgreen,16);
        DEBUG_SERIAL_PORT.print(sblue,16);
        DEBUG_SERIAL_PORT.print("|");
    }
    
    DEBUG_SERIAL_PORT.println("<MSG");
    #endif
   
}