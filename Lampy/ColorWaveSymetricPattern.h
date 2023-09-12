// ColorWaveSymetricPattern.h
#pragma once

#include <vector>
#include "LedColor.h"
#include "LedPattern.h"
#include "application.h"

class ColorWaveSymetricPattern : public LedPattern
{
    int mUpdateDelay = 125;
    int mColorCounter = 0;
    uint32_t mIterationCounter = 0;

    public: 
    ColorWaveSymetricPattern(int numLeds, Timer &timer);

    void Update() override;
};