// ColorWaveAsymetricPattern.h
#pragma once

#include <vector>
#include "LedColor.h"
#include "LedPattern.h"
#include "application.h"

class ColorWaveAsymetricPattern : public LedPattern
{
    int mUpdateDelay = 125;
    int mColorCounter = 0;
    uint32_t mIterationCounter = 0;

    public: 
    ColorWaveAsymetricPattern(int numLeds, Timer &timer);

    void Update() override;
};