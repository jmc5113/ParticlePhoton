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
static uint8_t s_baseColor[3] = {0x00, 0x00, 0x00};
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

ColorBloomPattern::ColorBloomPattern(int numLeds, Timer &timer) :
    LedPattern(timer, 175, numLeds),
    mRandomPosition(0),
    mDirPlus(0),
    mDirMinus(0)
{
    mRandomPosition = random(mNumLeds * 2);
    mDirPlus = mRandomPosition;
    mDirMinus = mRandomPosition;
    randomColor(s_bloomColor);
}

void ColorBloomPattern::SetLedAt(unsigned int index)
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

void ColorBloomPattern::Update()
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

    if(mDirMinus < 0 && mDirPlus >= mNumLeds * 2)
    {
        mRandomPosition = random(mNumLeds * 2);
        mDirPlus = mRandomPosition;
        mDirMinus = mRandomPosition;

        if(random(10) == 1)
        {
            s_bloomColor[0] = s_baseColor[0];
            s_bloomColor[1] = s_baseColor[1];
            s_bloomColor[2] = s_baseColor[2];
        }
        else if(s_randomizeColor)
        {
            randomColor(s_bloomColor);
        }
    }
}