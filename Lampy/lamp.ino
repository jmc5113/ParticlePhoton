// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
#include "ColorLED.h"
#include "HighPowerLed.h"
#include "TouchButton.h"
#include <vector>

// Patterns
#include "ColorWaveAsymetricPattern.h"
#include "ColorWaveSymetricPattern.h"
#include "ColorChasePattern.h"
#include "LedStackPattern.h"

#define NUM_LEDS 16

#define INTERRUPT_RESET_TIME 500 //time in ms for interrupt pins to wait before triggering again.

Adafruit_NeoPixel LedStrip1(NUM_LEDS, D2, WS2812B);
Adafruit_NeoPixel LedStrip2(NUM_LEDS, D3, WS2812B);

// Output PWM pin for high power led.
int highPowerLedEnPin = D0;
HighPowerLed highPowerLed = HighPowerLed(highPowerLedEnPin);

// Lamp Controls
int touchSensorPin = D4;
TouchButton touchButton = TouchButton(touchSensorPin);

// int decreaseBrightnessPin = D5;
// int increaseBrightnessPin = D6;

std::vector<ColorLED> g_ColorLEDs1(NUM_LEDS);
std::vector<ColorLED> g_ColorLEDs2(NUM_LEDS);

//////////
// colors
/////////
    // {0xFF, 0x00, 0x00}, // Red
    // {0xFF, 0x5F, 0x00}, // Red-Orange
    // {0xFF, 0x7F, 0x00}, // Orange
    // {0xFF, 0xFF, 0x00}, // Yellow
    // {0x00, 0xFF, 0x00}, // Green
    // {0x00, 0x3F, 0xFF}, // Light Blue
    // {0x00, 0xFF, 0xFF}, // Medium Blue
    // {0x00, 0x00, 0xFF}, // Blue
    // {0xFF, 0x00, 0xFF}, // Purple
    // {0xFF, 0x50, 0x7F}, // Light Pink
    // {0xFF, 0x00, 0x7F}, // Pink
    // {0xFF, 0xFF, 0xFF}, // White
    // {0x00, 0x00, 0x00}, // Dark

// Static handler functions 
void decreaseBrightness()
{
    highPowerLed.decreaseBrightness();
}

void increaseBrightness()
{
    highPowerLed.increaseBrightness();
}

void toggleHighPowerLed()
{
    highPowerLed.toggleHighPowerLed();
}

// Update the LEDs - executed rapidly for LEDs to make smooth color transitions
void updateLeds()
{
    for(int i = 0; i < NUM_LEDS; i++)
    {
        LedStrip1.setPixelColor(i, g_ColorLEDs1[i].UpdateLed());
        LedStrip2.setPixelColor(i, g_ColorLEDs2[i].UpdateLed());
    }

    LedStrip1.show();
    LedStrip2.show();
}
Timer ledUpdateTimer(20, updateLeds);

//
// Light show controls
//

void turnOffLightShow()
{
    // g_Timer.stopFromISR();
    ledUpdateTimer.stopFromISR();

    LedStrip1.clear();
    LedStrip2.clear();

    LedStrip1.show();
    LedStrip2.show();
}

void turnOnLightShow()
{
    // g_Timer.startFromISR();
    ledUpdateTimer.startFromISR();
}

int startTime = 0;
bool lightShowEnabled = false;
void toggleLightShow()
{
    if(lightShowEnabled)
    {
        lightShowEnabled = false;
        turnOffLightShow();
    }
    else
    {
        turnOnLightShow();
        lightShowEnabled = true;
    }
}

void setup() {
    highPowerLed.Initialize();

    touchButton.Initialize();
    touchButton.RegisterSingleTapHandler(toggleHighPowerLed);
    touchButton.RegisterDoubleTapHandler(toggleLightShow);
    touchButton.RegisterHoldHandler(decreaseBrightness);
    touchButton.RegisterTapAndHoldHandler(increaseBrightness);

    LedStrip1.begin();
    LedStrip2.begin();

    initializeColorChase(g_ColorLEDs1, g_ColorLEDs2);
    // initializeLedStack(NUM_LEDS, g_ColorLEDs1, g_ColorLEDs2);
    // initializeColorWaveSymetric(NUM_LEDS, g_ColorLEDs1, g_ColorLEDs2);
    // initializeColorWaveAsymetric(NUM_LEDS, g_ColorLEDs1, g_ColorLEDs2);

    ledUpdateTimer.start();
}

void loop() {

}