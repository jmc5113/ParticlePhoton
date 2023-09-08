#include "TouchButton.h"

//Singleton TouchButton.
static TouchButton* s_touchButton;

static void TouchSensorPinInterrupt()
{
    s_touchButton->InterruptTriggered();
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
    mTouchTimeoutTimer(500, TouchTimeoutExp),
    mTouchHold(false),
    mNumTaps(0),
    // mTouchTap(false),
    // mTouchDoubleTap(false),
    mInterruptTriggered(false)
{
    mTouchPin = sensorPin;
}

void TouchButton::Initialize()
{
    s_touchButton = this;
    pinMode(mTouchPin, INPUT);

    attachInterrupt(mTouchPin, TouchSensorPinInterrupt, CHANGE);

    mTouchHoldTimer.start();
    mTouchTimeoutTimer.start();
}

void TouchButton::InterruptTriggered()
{
    mInterruptTriggered = true;
}

void TouchButton::Update()
{
    if(mInterruptTriggered)
    {
        mInterruptTriggered = false;
        s_touchButton->TouchPinChange();
    }
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

    if(mNumTaps == 1)
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
    if(mNumTaps == 1)
    {
        mSingleTapHandler();
    }
    else if(mNumTaps == 2)
    {
        mDoubleTapHandler();
    }
    else if(mNumTaps == 3)
    {
        mTripleTapHandler();
    }

    mTouchHold = false;
    mNumTaps = 0;
    // mTouchTap = false;
    // mTouchDoubleTap = false;
}

void TouchButton::TouchPinChange()
{
    int value = digitalRead(mTouchPin);
    delay(50);
    int value2 = digitalRead(mTouchPin);

    // if interrupt pulse is too short, do nothing.
    if(value != value2)
        return;

    // Touch Active, else touch released
    if(value == HIGH)
    {
        // stop the timeout timer.
        mTouchTimeoutTimer.stop();

        //start a timer to see if this is a tap or hold
        mTouchHoldTimer.reset();
    }
    else
    {
        // Touch button released
        mTouchHoldTimer.stop();

        if(mTouchHold)
        {
            mTouchHold = false;
            mNumTaps = 0;
            // mTouchTap = false;
            // mTouchDoubleTap = false;
        }
        // else if(mTouchTap)
        // {
        //     // this is a double tap. Toggle the light show.
        //     mTouchTap = false;
        //     mTouchDoubleTap = true;
        //     mTouchTimeoutTimer.reset();
        // } 
        else
        {
            // this is a single tap, start the mTouchTimeoutTimer to see if another touch is coming.
            mNumTaps++;
            mTouchTimeoutTimer.reset();
        }

    } 
}
