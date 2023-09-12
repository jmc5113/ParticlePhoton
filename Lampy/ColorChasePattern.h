// ColorChasePattern.h
#pragma once

#include <vector>
#include <LedPattern.h>
#include "LedColor.h"
#include "application.h"

#define COLORS_8 8
static uint8_t redWhite[COLORS_8][3] = 
{
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x00, 0x00}, // Red
    {0x7F, 0x00, 0x00}, // Red
    {0xFF, 0xFF, 0xFF}, // White
    {0xFF, 0xFF, 0xFF}, // White
    {0xFF, 0xFF, 0xFF}, // White
    {0x7F, 0x7F, 0x7F}, // White
    
};

// #define COLORS_12 12
// static uint8_t redGreenBlueOrange[COLORS_12][3] =
// {
//     {0xFF, 0x00, 0x00}, // Red
//     {0xFF, 0x00, 0x00}, // Red
//     {0xFF, 0x00, 0x00}, // Red
//     {0x00, 0xFF, 0x00}, // Green
//     {0x00, 0xFF, 0x00}, // Green
//     {0x00, 0xFF, 0x00}, // Green
//     {0xFF, 0x7F, 0x00}, // Orange
//     {0xFF, 0x7F, 0x00}, // Orange
//     {0xFF, 0x7F, 0x00}, // Orange
//     {0x00, 0x00, 0xFF}, // Blue
//     {0x00, 0x00, 0xFF}, // Blue
//     {0x00, 0x00, 0xFF}, // Blue
// };

class ColorChasePattern : public LedPattern
{
    int mUpdateDelta = 10;
    int mUpdateDelay = 50;
    int mSpeedChangeTime = 0;
    bool mForward = true;
    uint8_t (*colors)[3] = redWhite; 
    int mNumColors = COLORS_8;
    uint32_t mIterationCounter = 0;

    public: 
    ColorChasePattern(int numLeds, Timer &timer);

    void Update() override;
};
