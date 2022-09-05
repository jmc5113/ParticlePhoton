////////////////////////////////////
// Color Wave Symetric Pattern
////////////////////////////////////
#include "ColorLED.h"

static int s_numLeds;
static ColorLED* s_ledStrip1;
static ColorLED* s_ledStrip2;

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

static int s_ledRunDelayTime = 125;
static int s_colorCounter = 0;
static uint32_t s_iterationCounter = 0;
void colorWaveSymetric()
{
    int n = s_iterationCounter % s_numLeds;
    if(n == 0)
    {
        s_colorCounter++;
        if(s_colorCounter == NUM_COLORS)
        {
            s_colorCounter = 0;
        }
    }

    int ledChangetime = s_ledRunDelayTime * 2;
    s_ledStrip1[n].ChangeLed(ledChangetime, s_waveColors[s_colorCounter][0], s_waveColors[s_colorCounter][1], s_waveColors[s_colorCounter][2]);
    s_ledStrip2[n].ChangeLed(ledChangetime, s_waveColors[s_colorCounter][0], s_waveColors[s_colorCounter][1], s_waveColors[s_colorCounter][2]);

    s_iterationCounter++;
}
Timer colorWaveTimer(s_ledRunDelayTime, colorWaveSymetric);

void initializeColorWaveSymetric(int numLeds, ColorLED* ledStrip1, ColorLED* ledStrip2)
{
    s_numLeds = numLeds;
    s_ledStrip1 = ledStrip1;
    s_ledStrip2 = ledStrip2;
    s_ledRunDelayTime = 125;
    s_colorCounter = 0;
    s_iterationCounter = 0;
    colorWaveTimer.start();
}