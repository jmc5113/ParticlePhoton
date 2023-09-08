//
// led stack pattern
//
#include "ColorBloomPattern.h"
#include "ColorHelper.h"

static int s_ledStackChangeTime = 250;
// static int mStackCount = 0;
// static int mLeadingPos = mNumLeds - 1;
// static int mTrailingPos = mNumLeds - 1;
// static int mResetPos = mNumLeds - 1;
// static uint8_t s_ledStackBaseColor[3] = {0x00, 0x00, 0x00};
static uint8_t s_bloomColor[3] = {0x00, 0xFF, 0x00};

static bool s_randomizeColor = true;

// There may be an issue with the LED pointers as one led from the mLedStrip1 is lit green, while mLedStrip2 works normal.

using namespace std;

// #define NUM_COLORS 10
// static uint8_t s_waveColors[NUM_COLORS][3] = 
// {
//     {0xFF, 0x00, 0x00}, // Red
//     {0xFF, 0x7F, 0x00}, // Orange
//     {0xFF, 0xFF, 0x00}, // Yellow
//     {0x00, 0xFF, 0x00}, // Green
//     {0x00, 0xFF, 0xFF}, // Light Blue
//     {0x00, 0x00, 0xFF}, // Blue
//     {0xFF, 0x00, 0xFF}, // Purple
//     {0xFF, 0x00, 0x7F}, // Pink
//     {0xFF, 0xFF, 0xFF}, // White
//     {0x00, 0x00, 0x00}  // Dark
// };

ColorBloomPattern::ColorBloomPattern(int numLeds) :
    LedPattern(175, &ColorBloomPattern::UpdateLeds, *this),
    mRandomPosition(0),
    mDirPlus(0),
    mDirMinus(0),
    mNumLeds(numLeds),
    mLedStrip1(vector<LedColor>(numLeds)),
    mLedStrip2(vector<LedColor>(numLeds))
{
    mRandomPosition = random(mNumLeds * 2);
    mDirPlus = mRandomPosition;
    mDirMinus = mRandomPosition;
    randomColor(s_bloomColor);
}

uint32_t ColorBloomPattern::GetLedColor_Strip1(unsigned int led)
{
    if(led < mLedStrip1.size())
        return mLedStrip1[led].UpdateLed();
    else
        return 0;
}

uint32_t ColorBloomPattern::GetLedColor_Strip2(unsigned int led)
{
    if(led < mLedStrip2.size())
        return mLedStrip2[led].UpdateLed();
    else
        return 0;
}

void ColorBloomPattern::SetLedAt(int index)
{
    if(index < mNumLeds)
    {
        mLedStrip1[index].ChangeLed(s_ledStackChangeTime, s_bloomColor[0], s_bloomColor[1], s_bloomColor[2]);
    }
    else 
    {
        mLedStrip2[mNumLeds * 2 - index].ChangeLed(s_ledStackChangeTime, s_bloomColor[0], s_bloomColor[1], s_bloomColor[2]);
    } 
}

void ColorBloomPattern::UpdateLeds()
{
    if(mRandomPosition == mDirPlus && mRandomPosition == mDirMinus)
    {
        SetLedAt(mRandomPosition);
        mDirPlus++;
        mDirMinus--;
        return;
    }

    if(mDirPlus < mNumLeds * 2)
    {
        SetLedAt(mDirPlus);
        mDirPlus++;
    }

    if(mDirMinus >= 0)
    {
        SetLedAt(mDirMinus);
        mDirMinus--;
    }

    if(mDirMinus <= 0 && mDirPlus >= mNumLeds * 2)
    {
        mRandomPosition = random(mNumLeds * 2);
        mDirPlus = mRandomPosition;
        mDirMinus = mRandomPosition;

        if(s_randomizeColor)
        {
            randomColor(s_bloomColor);
        }
    }
}