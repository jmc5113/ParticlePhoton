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

    int mNumLeds;
    std::vector<LedColor> mLedStrip1;
    std::vector<LedColor> mLedStrip2;


    public: 
    ColorWaveAsymetricPattern(int numLeds);

    void UpdateLeds();

    uint32_t GetLedColor_Strip1(unsigned int led) override;
    uint32_t GetLedColor_Strip2(unsigned int led) override;
};