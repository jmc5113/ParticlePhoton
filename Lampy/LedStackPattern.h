// LedStackPattern.h

#pragma once

#include <vector>
#include "LedColor.h"
#include "LedPattern.h"
#include "application.h"

class LedStackPattern : public LedPattern
{
private:
    int mStackCount;
    int mLeadingPos;
    int mTrailingPos;
    int mResetPos;
    int mCurrentColorIndex;

    void UpdateColor(); 

public: 
    LedStackPattern(int numLeds, Timer &timer);
    void Update() override;
};