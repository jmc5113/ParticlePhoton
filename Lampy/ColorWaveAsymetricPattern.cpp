////////////////////////////////////
// Color Wave Asymetric Pattern
////////////////////////////////////

#include "ColorLED.h"

static int s_numLeds;
static ColorLED* s_ledStrip1;
static ColorLED* s_ledStrip2;

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


static int ledRunDelayTimeA = 125;
static int colorCounterA = 0;
static uint32_t iterationCounterA = 0;
void colorWaveAsymetric()
{
    int n = iterationCounterA % s_numLeds;
    if(n == 0)
    {
        colorCounterA++;
        if(colorCounterA == NUM_COLORSA)
        {
            colorCounterA = 0;
        }
    }

    int ledChangetime = ledRunDelayTimeA * 2;
    s_ledStrip1[n].ChangeLed(ledChangetime, waveColorsLeft[colorCounterA][0], waveColorsLeft[colorCounterA][1], waveColorsLeft[colorCounterA][2]);
    s_ledStrip2[n].ChangeLed(ledChangetime, waveColorsRight[colorCounterA][0], waveColorsRight[colorCounterA][1], waveColorsRight[colorCounterA][2]);

    iterationCounterA++;
}
Timer colorWaveTimerAsym(ledRunDelayTimeA, colorWaveAsymetric);

void initializeColorWaveAsymetric(int numLeds, ColorLED* ledStrip1, ColorLED* ledStrip2)
{
    s_numLeds = numLeds;
    s_ledStrip1 = ledStrip1;
    s_ledStrip2 = ledStrip2;
    ledRunDelayTimeA = 125;
    colorCounterA = 0;
    iterationCounterA = 0;
    colorWaveTimerAsym.start();
}