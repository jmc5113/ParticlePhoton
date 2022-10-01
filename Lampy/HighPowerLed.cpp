#include "HighPowerLed.h"

HighPowerLed::HighPowerLed(int highPowerLedPin)
{
    mPwmPin = highPowerLedPin;
    mEnabled = false;
    mPwmValue = 255;
}

void HighPowerLed::Initialize()
{
    pinMode(mPwmPin, OUTPUT);

    analogWrite(mPwmPin, mPwmValue, 200);
}

void HighPowerLed::increaseBrightness()
{
    mPwmValue = max(mPwmValue - 10, 0);

    analogWrite(mPwmPin, mPwmValue, 200);
}

void HighPowerLed::decreaseBrightness()
{
    mPwmValue = min(mPwmValue + 10, 250);

    analogWrite(mPwmPin, mPwmValue, 200);
}

void HighPowerLed::toggleHighPowerLed()
{
    if(mEnabled)
    {
        // Turn off led
        analogWrite(mPwmPin, 255, 200);
        mEnabled = false;
    }
    else
    {
        // Set the PWM value back to where it was.
        analogWrite(mPwmPin, mPwmValue, 200);
        mEnabled = true;
    }
}
