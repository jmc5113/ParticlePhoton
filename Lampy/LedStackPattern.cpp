//
// led stack pattern
//
#include "LedStackPattern.h"
#include "ColorHelper.h"

static int s_ledStackChangeTime = 250;
// static int mStackCount = 0;
// static int mLeadingPos = mNumLeds - 1;
// static int mTrailingPos = mNumLeds - 1;
// static int mResetPos = mNumLeds - 1;
static uint8_t s_ledStackBaseColor[3] = {0x00, 0x00, 0x00};
static uint8_t s_ledStackColor[3] = {0x00, 0xFF, 0x00};

static bool s_randomizeStackColor = false;
static bool s_randomizeRunColor = false;

// There may be an issue with the LED pointers as one led from the mLedStrip1 is lit green, while mLedStrip2 works normal.

using namespace std;

#define NUM_COLORS 10
static uint8_t s_waveColors[NUM_COLORS][3] = 
{
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x7F, 0x00}, // Orange
    {0xFF, 0xFF, 0x00}, // Yellow
    {0x00, 0xFF, 0x00}, // Green
    {0x00, 0xFF, 0xFF}, // Light Blue
    {0x00, 0x00, 0xFF}, // Blue
    {0xFF, 0x00, 0xFF}, // Purple
    {0xFF, 0x00, 0x7F}, // Pink
    {0xFF, 0xFF, 0xFF}, // White
    {0x00, 0x00, 0x00}  // Dark
};

LedStackPattern::LedStackPattern(int numLeds) :
    mStackCount(0),
    mLeadingPos(numLeds - 1),
    mTrailingPos(numLeds - 1),
    mResetPos(numLeds - 1),
    LedPattern(175, &LedStackPattern::UpdateLeds, *this),
    mNumLeds(numLeds),
    mLedStrip1(vector<LedColor>(numLeds)),
    mLedStrip2(vector<LedColor>(numLeds))
{}

uint32_t LedStackPattern::GetLedColor_Strip1(unsigned int led)
{
    if(led < mLedStrip1.size())
        return mLedStrip1[led].UpdateLed();
    else
        return 0;
}

uint32_t LedStackPattern::GetLedColor_Strip2(unsigned int led)
{
    if(led < mLedStrip2.size())
        return mLedStrip2[led].UpdateLed();
    else
        return 0;
}

void LedStackPattern::UpdateLeds()
{
    if(mLeadingPos == mStackCount)
    {
        // reset down
        mLedStrip1[mResetPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);
        mLedStrip2[mResetPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);

        mResetPos--;
        if(mResetPos < 0)
        {
            mResetPos = mNumLeds - 1;
            mStackCount = 0;
            if(s_randomizeStackColor) 
            {
                randomColor(s_ledStackColor);
            }
        }
        return;
    }

    if(mTrailingPos - mLeadingPos > 1)
    {
        // Set led at mTrailingPos back to the base color
        mLedStrip1[mTrailingPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);
        mLedStrip2[mTrailingPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);
        mTrailingPos --;
    }

    mLeadingPos --;

    // Set the next led to the stack color
    mLedStrip1[mLeadingPos].ChangeLed(s_ledStackChangeTime, s_ledStackColor[0], s_ledStackColor[1], s_ledStackColor[2]);
    mLedStrip2[mLeadingPos].ChangeLed(s_ledStackChangeTime, s_ledStackColor[0], s_ledStackColor[1], s_ledStackColor[2]);

    if(mLeadingPos < 0)
    {
        mLeadingPos = mNumLeds - 1;
    }

    if(mTrailingPos < 0)
    {
        mTrailingPos = mNumLeds - 1;
    }

    if(mLeadingPos == mStackCount)
    {
        mLeadingPos = mTrailingPos = mNumLeds - 1;
        
        mStackCount++;

        if(s_randomizeRunColor)
        {
            randomColor(s_ledStackColor);
        }

        if(mStackCount == mNumLeds)
        {
            mStackCount = 0;
        }
    }
}