////////////////////////////////////
// Color Chase Pattern
////////////////////////////////////

#include "ColorLED.h"
#include <vector>

using namespace std;

static int s_numLeds;
static vector<ColorLED*> &s_ledStrip1;
static vector<ColorLED*> &s_ledStrip2;


#define COLORS_8 8
uint8_t redWhite[COLORS_8][3] = 
{
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x00, 0x00}, // Red
    {0x7F, 0x00, 0x00}, // Red
    {0xFF, 0xFF, 0xFF}, // White
    {0xFF, 0xFF, 0xFF}, // White
    {0xFF, 0xFF, 0xFF}, // White
    {0x7F, 0x7F, 0x7F}, // White
    
};

#define COLORS_12 12
uint8_t redGreenBlueOrange[COLORS_12][3] =
{
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x00, 0x00}, // Red
    {0xFF, 0x00, 0x00}, // Red
    {0x00, 0xFF, 0x00}, // Green
    {0x00, 0xFF, 0x00}, // Green
    {0x00, 0xFF, 0x00}, // Green
    {0xFF, 0x7F, 0x00}, // Orange
    {0xFF, 0x7F, 0x00}, // Orange
    {0xFF, 0x7F, 0x00}, // Orange
    {0x00, 0x00, 0xFF}, // Blue
    {0x00, 0x00, 0xFF}, // Blue
    {0x00, 0x00, 0xFF}, // Blue
};

int colorChaseSpeedUpdateDelta = 10;
int colorChaseRunDelay = 50;
int speedChangeTime = 0;
bool forward = true;
uint8_t (*colors)[3] = redWhite; 
int numColors = COLORS_8;
uint32_t iterationCounter = 0;


void colorChase();

Timer colorChaseTimer(colorChaseRunDelay, colorChase);
void colorChase()
{
    int currentTime = millis();
    if(currentTime - speedChangeTime > 500)
    {
        speedChangeTime = currentTime;
        if(colorChaseRunDelay <= 50)
        {
            colorChaseSpeedUpdateDelta = 10;

        }
        else if(colorChaseRunDelay >= 500)
        {
            colorChaseSpeedUpdateDelta = -10;
            forward = !forward;
        }

        colorChaseRunDelay += colorChaseSpeedUpdateDelta;
        colorChaseTimer.changePeriodFromISR(colorChaseRunDelay);
    }

    int colorCounter = iterationCounter;
    for(int i = 0; i < s_numLeds; i++)
    {
        int changetime = colorChaseRunDelay - 30;

        if(forward)
        {
            s_ledStrip1[i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
            s_ledStrip2[15 - i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
        }
        else
        {
            s_ledStrip1[15 - i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
            s_ledStrip2[i].ChangeLed(changetime, colors[colorCounter][0], colors[colorCounter][1], colors[colorCounter][2]);
        }
        
        colorCounter++;
        colorCounter = colorCounter % numColors;
    }

    iterationCounter++;
    iterationCounter = iterationCounter % numColors;
}

void initializeColorChase(std::vector<ColorLED> &ledStrip1, std::vector<ColorLED> &ledStrip2)
{
    s_numLeds = s_ledStrip1.size();
    s_ledStrip1 = ledStrip1;
    s_ledStrip2 = ledStrip2;
    colorChaseTimer.start();
    // colorChaseSpeedTimer.start();
}