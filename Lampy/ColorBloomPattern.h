// ColorBloomPattern.h

#pragma once

#include <vector>
#include "LedColor.h"
#include "LedPattern.h"
#include "application.h"

class ColorBloomPattern : public LedPattern
{
    int mRandomPosition;
    int mDirPlus;
    int mDirMinus;

    int mNumLeds;
    std::vector<LedColor> mLedStrip1;
    std::vector<LedColor> mLedStrip2;

    public: 
    ColorBloomPattern(int numLeds);

    void UpdateLeds();

    void SetLedAt(int index);

    uint32_t GetLedColor_Strip1(unsigned int led) override;
    uint32_t GetLedColor_Strip2(unsigned int led) override;
};