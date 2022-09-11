#include "TouchButton.h"

//Singleton TouchButton.
static TouchButton* s_touchButton;

static void TouchSensorPinInterrupt()
{
    s_touchButton->TouchPinChange();
}

static void TouchHoldTimerExp()
{
    s_touchButton->TouchHoldTimeout();
}

static void TouchTimeoutExp()
{
    s_touchButton->TouchTimeout();
}

TouchButton::TouchButton(int sensorPin) :
    mTouchHoldTimer(300, TouchHoldTimerExp), 
    mTouchTimeoutTimer(500, TouchTimeoutExp)
{
    mTouchPin = sensorPin;
    mTouchHold = false;
    mTouchTap = false;
    mTouchDoubleTap = false;
}

void TouchButton::Initialize()
{
    s_touchButton = this;
    pinMode(mTouchPin, INPUT);

    attachInterrupt(mTouchPin, TouchSensorPinInterrupt, CHANGE);

    mTouchHoldTimer.start();
    mTouchTimeoutTimer.start();
}

void TouchButton::RegisterSingleTapHandler(TouchButtonHandler handler)
{
    mSingleTapHandler = handler;
}

void TouchButton::RegisterDoubleTapHandler(TouchButtonHandler handler)
{
    mDoubleTapHandler = handler;
}

void TouchButton::RegisterHoldHandler(TouchButtonHandler handler)
{
    mHoldHandler = handler;
}

void TouchButton::RegisterTapAndHoldHandler(TouchButtonHandler handler)
{
    mTapAndHoldHandler = handler;
}

void TouchButton::RegisterTripleTapHandler(TouchButtonHandler handler)
{
    mTripleTapHandler = handler;
}


void TouchButton::TouchHoldTimeout()
{
    mTouchHold = true;

    if(mTouchTap)
    {
        // Tap and hold
        mTapAndHoldHandler();
    }
    else
    {
        // Hold
        mHoldHandler();
    }
}

void TouchButton::TouchTimeout()
{
    if(mTouchTap)
    {
        mSingleTapHandler();
    }
    else if(mTouchDoubleTap)
    {
        mDoubleTapHandler();
    }

    mTouchHold = false;
    mTouchTap = false;
    mTouchDoubleTap = false;
}

void TouchButton::TouchPinChange()
{
    int value = digitalRead(mTouchPin);

    // Touch Active, else touch released
    if(value == HIGH)
    {
        // stop the timeout timer.
        mTouchTimeoutTimer.stopFromISR();

        //start a timer to see if this is a tap or hold
        mTouchHoldTimer.resetFromISR();
    }
    else
    {
        // Touch button released
        mTouchHoldTimer.stopFromISR();

        if(mTouchHold)
        {
            mTouchHold = false;
            mTouchTap = false;
            mTouchDoubleTap = false;
        }
        else if(mTouchTap)
        {
            // this is a double tap. Toggle the light show.
            mTouchTap = false;
            mTouchDoubleTap = true;
            mTouchTimeoutTimer.resetFromISR();
        } 
        else
        {
            // this is a single tap, start the mTouchTimeoutTimer to see if another touch is coming.
            mTouchTap = true;
            mTouchTimeoutTimer.resetFromISR();
        }

    } 
}
