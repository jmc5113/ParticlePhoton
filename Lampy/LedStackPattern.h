// LedStackPattern.h

#pragma once

#include <vector>
#include "LedColor.h"
#include "LedPattern.h"
#include "application.h"

class LedStackPattern : public LedPattern
{
    int mStackCount;
    int mLeadingPos;
    int mTrailingPos;
    int mResetPos;

    int mNumLeds;
    std::vector<LedColor> mLedStrip1;
    std::vector<LedColor> mLedStrip2;

    public: 
    LedStackPattern(int numLeds);

    void UpdateLeds();

    uint32_t GetLedColor_Strip1(unsigned int led) override;
    uint32_t GetLedColor_Strip2(unsigned int led) override;
};