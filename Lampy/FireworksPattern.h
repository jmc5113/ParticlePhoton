// FireworksPattern.h

#pragma once

#include <vector>
#include "LedColor.h"
#include "LedPattern.h"
#include "application.h"

class FireworksPattern : public LedPattern
{
    int8_t mRandomPosition;
    int8_t mDirPlus;
    bool mDirPlusComplete;
    int8_t mDirMinus;
    bool mDirMinusComplete;
    int8_t mRandomLength;
    float mFade;
    int8_t mSpeed;
    int8_t mSpeedCount;
    int8_t mSparkle1Position;
    int8_t mSparkle2Position;
    int8_t mSparkle3Position;
    int8_t mSparkle1Count;
    int8_t mSparkle2Count;
    int8_t mSparkle3Count;
    bool mSparkle1On;
    bool mSparkle2On;
    bool mSparkle3On;

    public: 
    FireworksPattern(int numLeds, Timer &timer);
    void Update() override;

    private:
    void UpdateSparkles();
    void FadeColor();
    void SetLedAt(int8_t index, uint8_t *color, uint32_t changeTime);
};