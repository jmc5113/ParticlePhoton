////////////////////////////////////
// Color Chase Pattern
////////////////////////////////////

#include "ColorChasePattern.h"

using namespace std;

ColorChasePattern::ColorChasePattern(int numLeds) : 
    LedPattern(50, &ColorChasePattern::UpdateLeds, *this),
    mNumLeds(numLeds),
    mLedStrip1(vector<LedColor>(numLeds)),
    mLedStrip2(vector<LedColor>(numLeds))
{}

uint32_t ColorChasePattern::GetLedColor_Strip1(unsigned int led)
{
    if(led < mLedStrip1.size())
        return mLedStrip1[led].UpdateLed();
    else
        return 0;
}

uint32_t ColorChasePattern::GetLedColor_Strip2(unsigned int led)
{
    if(led < mLedStrip2.size())
        return mLedStrip2[led].UpdateLed();
    else
        return 0;
}

// Timer colorChaseTimer(mUpdateDelay, ColorChasePattern::UpdateLeds);
void ColorChasePattern::UpdateLeds()
{
    int currentTime = millis();
    if(currentTime - mSpeedChangeTime > 500)
    {
        mSpeedChangeTime = currentTime;
        if(mUpdateDelay <= 50)
        {
            mUpdateDelta = 10;

        }
        else if(mUpdateDelay >= 500)
        {
            mUpdateDelta = -10;
            mForward = !mForward;
        }

        mUpdateDelay += mUpdateDelta;
        mTimer.changePeriodFromISR(mUpdateDelay);
    }

    int colorCounter = mIterationCounter;
    for(int i = 0; i < mNumLeds; i++)
    {
        int changetime = mUpdateDelay - 30;

        if(mForward)
        {
            mLedStrip1[i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
            mLedStrip2[15 - i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
        }
        else
        {
            mLedStrip1[15 - i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
            mLedStrip2[i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
        }
        
        colorCounter++;
        colorCounter = colorCounter % mNumColors;
    }

    mIterationCounter++;
    mIterationCounter = mIterationCounter % mNumColors;
}
