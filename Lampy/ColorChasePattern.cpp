////////////////////////////////////
// Color Chase Pattern
////////////////////////////////////

#include "ColorChasePattern.h"

using namespace std;

ColorChasePattern::ColorChasePattern(int numLeds, Timer &timer) : 
    LedPattern(timer, 50, numLeds)
{}

void ColorChasePattern::Update()
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
