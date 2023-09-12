//
// led stack pattern
//
#include "FireworksPattern.h"
#include "ColorHelper.h"

static int s_changeTime = 250;
static int s_resetChangeTime = 100;
static uint8_t s_baseColor[3] = {0x00, 0x00, 0x00};
static uint8_t s_bloomColor[3] = {0x00, 0xFF, 0x00};

static int s_delta = 4;
static int s_maxLength = 8;
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

FireworksPattern::FireworksPattern(int numLeds, Timer &timer) :
    LedPattern(timer, 15, numLeds),
    mRandomPosition(0),
    mDirPlus(0),
    mDirPlusComplete(false),
    mDirMinus(0),
    mDirMinusComplete(false),
    mFade(.95),
    mSpeed(0),
    mSpeedCount(0)
{
    mRandomPosition = random(mNumLeds * 2 - 10) + 5;
    mDirPlus = mRandomPosition;
    mDirMinus = mRandomPosition;
    randomColor(s_bloomColor);
    mRandomLength = random(s_maxLength) + 5;

    // Sparkles
    mSparkle1Position = random(mTotalLeds);
    mSparkle1Count = random(50) + 20;
    mSparkle2Position = random(mTotalLeds);
    mSparkle2Count = random(50) + 20;
    mSparkle3Position = random(mTotalLeds);
    mSparkle3Count = random(50) + 20;
}

void FireworksPattern::SetLedAt(int8_t index, uint8_t *color, uint32_t changeTime)
{
    if(index < mNumLeds)
    {
        mLedStrip1[index].ChangeLed(changeTime, color[0], color[1], color[2]);
    }
    else 
    {
        mLedStrip2[mNumLeds * 2 - index].ChangeLed(changeTime, color[0], color[1], color[2]);
    } 
}

void FireworksPattern::FadeColor()
{
    s_bloomColor[0] = s_bloomColor[0] * mFade;
    s_bloomColor[1] = s_bloomColor[1] * mFade;
    s_bloomColor[2] = s_bloomColor[2] * mFade;
    mFade -= .05;
}

void FireworksPattern::UpdateSparkles()
{
    // Sparkles
    if(mSparkle1On)
    {
        SetLedAt(mSparkle1Position, s_baseColor, 1000);
        mSparkle1On = false;
    }
    if(mSparkle2On)
    {
        SetLedAt(mSparkle2Position, s_baseColor, 850);
        mSparkle2On = false;
    }
    if(mSparkle3On)
    {
        SetLedAt(mSparkle3Position, s_baseColor, 650);
        mSparkle3On = false;
    }

    mSparkle1Count--;
    mSparkle2Count--;
    mSparkle3Count--;

    if(mSparkle1Count == 0)
    {
        mSparkle1Count = random(50) + 20;
        mSparkle1Position = random(mTotalLeds);
        SetLedAt(mSparkle1Position, g_colorWhite, 15);
        mSparkle1On = true;
    }

    if(mSparkle2Count == 0)
    {
        mSparkle2Count = random(50) + 20;
        mSparkle2Position = random(mTotalLeds);
        SetLedAt(mSparkle2Position, g_colorWhite, 15);
        mSparkle2On = true;
    }

    if(mSparkle3Count == 0)
    {
        mSparkle3Count = random(50) + 20;
        mSparkle3Position = random(mTotalLeds);
        SetLedAt(mSparkle3Position, g_colorWhite, 15);
        mSparkle3On = true;
    }
}

void FireworksPattern::Update()
{
    UpdateSparkles();

    // Fireworks
    if(mRandomPosition == mDirPlus && mRandomPosition == mDirMinus)
    {
        SetLedAt(mRandomPosition, s_bloomColor,s_changeTime);
        mDirPlus++;
        mDirMinus--;
        return;
    }

    if(mSpeedCount > 0)
    {
        mSpeedCount--;
        return;
    }

    mSpeed++;
    mSpeedCount = mSpeed;
    FadeColor();

    mDirPlus++;
    int dirPlusMinusDelta = mDirPlus - s_delta;

    if(dirPlusMinusDelta >= mRandomPosition && dirPlusMinusDelta < mNumLeds * 2)
        SetLedAt(dirPlusMinusDelta, s_baseColor, s_resetChangeTime);
    
    if(mDirPlus < mNumLeds * 2 && mDirPlus <= mRandomPosition + mRandomLength)
    {
        SetLedAt(mDirPlus, s_bloomColor, s_changeTime);
    }
    else if(dirPlusMinusDelta == mNumLeds * 2 - 1 || dirPlusMinusDelta == mRandomPosition + mRandomLength)
    {
        mDirPlusComplete = true;
    }

    mDirMinus--;
    int dirMinusPlusDelta = mDirMinus + s_delta;

    // Reset LEDs back to base color
    if(dirMinusPlusDelta <= mRandomPosition && dirMinusPlusDelta >= 0)
        SetLedAt(dirMinusPlusDelta, s_baseColor, s_resetChangeTime);
    
    // Set LEDs to firework color.
    if(mDirMinus >= 0 && mDirMinus >= mRandomPosition - mRandomLength)
    {
        SetLedAt(mDirMinus, s_bloomColor, s_changeTime);
    }
    else if(dirMinusPlusDelta == 0 || dirMinusPlusDelta == mRandomPosition - mRandomLength)
    {
        mDirMinusComplete = true;
    }

    if(mDirMinusComplete && mDirPlusComplete)
    {
        mRandomPosition = random(mNumLeds * 2 - 10) + 5;
        mRandomLength = random(s_maxLength) + 5;
        mDirPlus = mRandomPosition;
        mDirMinus = mRandomPosition;
        mDirPlusComplete = false;
        mDirMinusComplete = false;
        mSpeed = 0;
        mSpeedCount = 0;
        mFade = .95;

        if(s_randomizeColor)
        {
            randomColor(s_bloomColor);
        }
    }
}