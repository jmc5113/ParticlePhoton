#pragma once

#include <stdint.h>
#include "application.h"

class LedPattern {
    protected:
    Timer mTimer;

    public:
    template <typename T>
    LedPattern(unsigned int updateDelay, void (T::*handler)(), T& instance) : 
        mTimer(updateDelay, handler, instance)
    {}

    ~LedPattern()
    {
        mTimer.dispose();
    }

    void Start(){
        mTimer.start();
    }

    void Stop(){
        mTimer.stop();
    }

    void StartFromISR(){
        mTimer.startFromISR();
    }

    void StopFromISR(){
        mTimer.stopFromISR();
    }

    virtual uint32_t GetLedColor_Strip1(unsigned int led) = 0;
    virtual uint32_t GetLedColor_Strip2(unsigned int led) = 0;
};