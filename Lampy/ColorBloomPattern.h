// ColorBloomPattern.h

#pragma once

#include <vector>
#include "LedColor.h"
#include "LedPattern.h"
#include "application.h"

class ColorBloomPattern : public LedPattern
{
private:
    int mRandomPosition;
    int mDirPlus;
    int mDirMinus;

    void SetLedAt(unsigned int index);

public: 
    ColorBloomPattern(int numLeds, Timer &timer);

    void Update() override;

};