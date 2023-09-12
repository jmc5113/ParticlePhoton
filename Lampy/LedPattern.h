#pragma once

#include <stdint.h>
#include <vector>

#include "application.h"

#include "LedColor.h"

class LedPattern {
protected:
    unsigned int mUpdateDelay;
    Timer &mTimer;
    unsigned int mNumLeds;
    unsigned int mTotalLeds;
    std::vector<LedColor> mLedStrip1;
    std::vector<LedColor> mLedStrip2;

public:
    // template <typename T>
    LedPattern(Timer &timer, unsigned int updateDelay, int numLeds) : //void (T::*handler)(), T& instance) :
        mUpdateDelay(updateDelay),
        mTimer(timer),
        mNumLeds(numLeds),
        mTotalLeds(numLeds * 2),
        // mHandler(handler),
        mLedStrip1(std::vector<LedColor>(numLeds)),
        mLedStrip2(std::vector<LedColor>(numLeds))
    {}

    void Start(){
        mTimer.changePeriod(mUpdateDelay);
        mTimer.start();
    }

    void Stop(){
        mTimer.stop();
    }

    void StartFromISR(){
        mTimer.changePeriodFromISR(mUpdateDelay);
        mTimer.startFromISR();
    }

    void StopFromISR(){
        mTimer.stopFromISR();
    }

    uint32_t GetLedColor_Strip1(unsigned int led)
    {
        if(led < mLedStrip1.size())
            return mLedStrip1[led].UpdateLed();
        else
            return 0;
    }

    uint32_t GetLedColor_Strip2(unsigned int led)
    {
        if(led < mLedStrip2.size())
            return mLedStrip2[led].UpdateLed();
        else
            return 0;
    }

    virtual void Update() = 0;
};