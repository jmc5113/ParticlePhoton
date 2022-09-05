//
// led stack pattern
//
#include "ColorLED.h"
#include "ColorHelper.h"

static int s_numLeds;
static ColorLED* s_ledStrip1;
static ColorLED* s_ledStrip2;

static int s_ledStackChangeTime = 250;
static int s_stackCount = 0;
static int s_leadingPos = s_numLeds - 1;
static int s_trailingPos = s_numLeds - 1;
static int s_resetPos = s_numLeds - 1;
static uint8_t s_ledStackBaseColor[3] = {0x00, 0x00, 0x00};
static uint8_t s_ledStackColor[3] = {0x00, 0xFF, 0x00};

static bool s_randomizeStackColor = false;
static bool s_randomizeRunColor = false;

// There may be an issue with the LED pointers as one led from the s_ledstrip1 is lit green, while s_ledstrip2 works normal.

void ledStack()
{
    if(s_leadingPos == s_stackCount)
    {
        // reset down
        s_ledStrip1[s_resetPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);
        // s_ledStrip2[s_resetPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);

        s_resetPos--;
        if(s_resetPos < 0)
        {
            s_resetPos = s_numLeds - 1;
            s_stackCount = 0;
            if(s_randomizeStackColor) 
            {
                randomColor(s_ledStackColor);
            }
        }
        return;
    }

    if(s_trailingPos - s_leadingPos > 1)
    {
        // Set led at s_trailingPos back to the base color
        s_ledStrip1[s_trailingPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);
        // s_ledStrip2[s_trailingPos].ChangeLed(s_ledStackChangeTime, s_ledStackBaseColor[0], s_ledStackBaseColor[1], s_ledStackBaseColor[2]);
        s_trailingPos --;
    }

    s_leadingPos --;

    // Set the next led to the stack color
    s_ledStrip1[s_leadingPos].ChangeLed(s_ledStackChangeTime, s_ledStackColor[0], s_ledStackColor[1], s_ledStackColor[2]);
    // s_ledStrip2[s_leadingPos].ChangeLed(s_ledStackChangeTime, s_ledStackColor[0], s_ledStackColor[1], s_ledStackColor[2]);

    if(s_leadingPos < 0)
    {
        s_leadingPos = s_numLeds - 1;
    }

    if(s_trailingPos < 0)
    {
        s_trailingPos = s_numLeds - 1;
    }

    if(s_leadingPos == s_stackCount)
    {
        s_leadingPos = s_trailingPos = s_numLeds - 1;
        
        s_stackCount++;

        if(s_randomizeRunColor)
        {
            randomColor(s_ledStackColor);
        }

        if(s_stackCount == s_numLeds)
        {
            s_stackCount = 0;
        }
    }
}

Timer ledStackTimer(175, ledStack);
void initializeLedStack(int numLeds, ColorLED* ledStrip1, ColorLED* ledStrip2)
{
    s_numLeds = numLeds;
    s_ledStrip1 = ledStrip2;
    s_ledStrip2 = ledStrip2;
    ledStackTimer.start();
}