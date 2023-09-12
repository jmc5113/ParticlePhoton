// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
#include "LedColor.h"
#include "HighPowerLed.h"
#include "TouchButton.h"
#include <vector>
#include <memory>

// Patterns
#include "ColorWaveAsymetricPattern.h"
#include "ColorWaveSymetricPattern.h"
#include "ColorChasePattern.h"
#include "LedStackPattern.h"
#include "ColorBloomPattern.h"
#include "FireworksPattern.h"

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


Timer PatternUpdateTimer(1000, patternUpdate);

std::vector<std::shared_ptr<LedPattern>> ledPatterns = {
    std::make_shared<ColorBloomPattern>(NUM_LEDS, PatternUpdateTimer),
    std::make_shared<FireworksPattern>(NUM_LEDS, PatternUpdateTimer),
    std::make_shared<ColorChasePattern>(NUM_LEDS, PatternUpdateTimer),
    std::make_shared<ColorWaveSymetricPattern>(NUM_LEDS, PatternUpdateTimer),
    std::make_shared<ColorWaveAsymetricPattern>(NUM_LEDS, PatternUpdateTimer),
    std::make_shared<LedStackPattern>(NUM_LEDS, PatternUpdateTimer)
};
int vector_size = 0;
int currentLedPattern = 0;

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

void patternUpdate()
{
    // Log.info("Call patternUpdate");
    ledPatterns[currentLedPattern]->Update();
}

// Update the LEDs - executed rapidly for LEDs to make smooth color transitions
void updateLeds()
{
    for(int i = 0; i < NUM_LEDS; i++)
    {
        LedStrip1.setPixelColor(i, ledPatterns[currentLedPattern]->GetLedColor_Strip1(i));
        LedStrip2.setPixelColor(i, ledPatterns[currentLedPattern]->GetLedColor_Strip2(i));
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
    ledUpdateTimer.stopFromISR();

    ledPatterns[currentLedPattern]->StopFromISR();

    LedStrip1.clear();
    LedStrip2.clear();

    LedStrip1.show();
    LedStrip2.show();
}

void turnOnLightShow()
{
    ledPatterns[currentLedPattern]->StartFromISR();
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

void cyclePatterns()
{
    ledPatterns[currentLedPattern]->Stop();
    currentLedPattern++;

    if(currentLedPattern >= ledPatterns.size())
    {
        currentLedPattern = 0;
    }

    ledPatterns[currentLedPattern]->Start();
}

void setup() {
    highPowerLed.Initialize();

    touchButton.Initialize();
    touchButton.RegisterSingleTapHandler(toggleHighPowerLed);
    touchButton.RegisterDoubleTapHandler(toggleLightShow);
    touchButton.RegisterTripleTapHandler(cyclePatterns);
    touchButton.RegisterHoldHandler(decreaseBrightness);
    touchButton.RegisterTapAndHoldHandler(increaseBrightness);
    LedStrip1.begin();
    LedStrip2.begin();

    ledPatterns[currentLedPattern]->Start();
    ledUpdateTimer.start();
    
    // Particle.variable("Vector_Size", vector_size);
    // Particle.variable("CurrentPattern", currentLedPattern);

    // Log.info("Finish Setup");
}

void loop() {
    touchButton.Update();
}