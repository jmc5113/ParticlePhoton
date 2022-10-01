#include "LedColor.h"

#include <stdint.h>
#include <neopixel.h>

static Adafruit_NeoPixel LedStrip1(1, D1, WS2812B);

uint32_t LedColor::UpdateLed()
{
    if(mChangeTime == 0)
    {
        return mCurrentColor;
    }

    float timeElapsed = millis() - mChangeStartTime;
    float percent = timeElapsed / mChangeTime;

    if(percent > 1)
    {
        percent = 1;
    }

    int8_t deltaRed = (mTargetRed - mCurrentRed) * percent;
    int8_t deltaGreen = (mTargetGreen - mCurrentGreen) * percent;
    int8_t deltaBlue = (mTargetBlue - mCurrentBlue) * percent;

    if(percent == 1)
    {
        mChangeTime = 0;
        mCurrentRed = mTargetRed;
        mCurrentGreen = mTargetGreen;
        mCurrentBlue = mTargetBlue;
        mCurrentColor = LedStrip1.Color(mCurrentRed, mCurrentGreen, mCurrentBlue);
    }
    else
    {
        mCurrentColor = LedStrip1.Color(mCurrentRed + deltaRed, 
                                        mCurrentGreen + deltaGreen,
                                        mCurrentBlue + deltaBlue);
    }
    

    return mCurrentColor;
}

void LedColor::ChangeLed(uint32_t changeTime, uint8_t targetR, uint32_t targetG, uint32_t targetB)
{
    mChangeTime = changeTime;
    mTargetRed = targetR;
    mTargetGreen = targetG;
    mTargetBlue = targetB;

    mChangeStartTime = millis();
}

void LedColor::TurnOff()
{
    mCurrentColor = 0;
}