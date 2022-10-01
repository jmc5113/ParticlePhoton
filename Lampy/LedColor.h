#pragma once

#include "application.h"

class LedColor
{
    uint32_t mCurrentColor;
    uint8_t mTargetRed;
    uint8_t mCurrentRed;
    uint8_t mTargetGreen;
    uint8_t mCurrentGreen;
    uint8_t mTargetBlue;
    uint8_t mCurrentBlue;
    uint32_t mChangeTime;
    uint32_t mChangeStartTime;

public:

    uint32_t UpdateLed();
    void ChangeLed(uint32_t changeTime, uint8_t targetR, uint32_t targetG, uint32_t targetB);
    void TurnOff();
};
