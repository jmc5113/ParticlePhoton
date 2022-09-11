////////////////////////////////////
// Color Wave Asymetric Pattern
////////////////////////////////////
#include "ColorWaveAsymetricPattern.h"

using namespace std;


#define NUM_COLORSA 3
uint8_t waveColorsLeft[NUM_COLORSA][3] = 
{
    {0xFF, 0x00, 0xFF}, // Purple
    // {0xFF, 0x00, 0x7F}, // Pink
    {0xFF, 0x50, 0x7F}, // Light Pink
    {0xFF, 0x00, 0x00}, // Red
};

uint8_t waveColorsRight[NUM_COLORSA][3] = 
{
    // {0xFF, 0x00, 0x7F}, // Pink
    {0xFF, 0x50, 0x7F}, // Light Pink
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x00, 0xFF}, // Purple
};


ColorWaveAsymetricPattern::ColorWaveAsymetricPattern(int numLeds) : 
    LedPattern(125, &ColorWaveAsymetricPattern::UpdateLeds, *this),
    mNumLeds(numLeds),
    mLedStrip1(vector<LedColor>(numLeds)),
    mLedStrip2(vector<LedColor>(numLeds))
{}

uint32_t ColorWaveAsymetricPattern::GetLedColor_Strip1(unsigned int led)
{
    if(led < mLedStrip1.size())
        return mLedStrip1[led].UpdateLed();
    else
        return 0;
}

uint32_t ColorWaveAsymetricPattern::GetLedColor_Strip2(unsigned int led)
{
    if(led < mLedStrip2.size())
        return mLedStrip2[led].UpdateLed();
    else
        return 0;
}

void ColorWaveAsymetricPattern::UpdateLeds()
{
    int n = mIterationCounter % mNumLeds;
    if(n == 0)
    {
        mColorCounter++;
        if(mColorCounter == NUM_COLORSA)
        {
            mColorCounter = 0;
        }
    }

    int ledChangetime = mUpdateDelay * 2;
    mLedStrip1[n].ChangeLed(ledChangetime, waveColorsLeft[mColorCounter][0], waveColorsLeft[mColorCounter][1], waveColorsLeft[mColorCounter][2]);
    mLedStrip2[n].ChangeLed(ledChangetime, waveColorsRight[mColorCounter][0], waveColorsRight[mColorCounter][1], waveColorsRight[mColorCounter][2]);

    mIterationCounter++;
}