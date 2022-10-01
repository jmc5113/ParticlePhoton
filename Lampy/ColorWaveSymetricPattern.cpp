////////////////////////////////////
// Color Wave Symetric Pattern
////////////////////////////////////
#include "ColorWaveSymetricPattern.h"

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

ColorWaveSymetricPattern::ColorWaveSymetricPattern(int numLeds) : 
    LedPattern(125, &ColorWaveSymetricPattern::UpdateLeds, *this),
    mNumLeds(numLeds),
    mLedStrip1(vector<LedColor>(numLeds)),
    mLedStrip2(vector<LedColor>(numLeds))
{}

uint32_t ColorWaveSymetricPattern::GetLedColor_Strip1(unsigned int led)
{
    if(led < mLedStrip1.size())
        return mLedStrip1[led].UpdateLed();
    else
        return 0;
}

uint32_t ColorWaveSymetricPattern::GetLedColor_Strip2(unsigned int led)
{
    if(led < mLedStrip2.size())
        return mLedStrip2[led].UpdateLed();
    else
        return 0;
}

void ColorWaveSymetricPattern::UpdateLeds()
{
    int n = mIterationCounter % mNumLeds;
    if(n == 0)
    {
        mColorCounter++;
        if(mColorCounter == NUM_COLORS)
        {
            mColorCounter = 0;
        }
    }

    int ledChangetime = mUpdateDelay * 2;
    mLedStrip1[n].ChangeLed(ledChangetime, s_waveColors[mColorCounter][0], s_waveColors[mColorCounter][1], s_waveColors[mColorCounter][2]);
    mLedStrip2[n].ChangeLed(ledChangetime, s_waveColors[mColorCounter][0], s_waveColors[mColorCounter][1], s_waveColors[mColorCounter][2]);

    mIterationCounter++;
}