#include "application.h"

typedef void (*TouchButtonHandler)();

class TouchButton
{
private:
    int mTouchPin;
    int mNumTaps;
    bool mTouchHold;
    bool mInterruptTriggered;
    Timer mTouchHoldTimer;
    Timer mTouchTimeoutTimer;

    TouchButtonHandler mSingleTapHandler;
    TouchButtonHandler mDoubleTapHandler;
    TouchButtonHandler mHoldHandler;
    TouchButtonHandler mTapAndHoldHandler;
    TouchButtonHandler mTripleTapHandler;

public:
    TouchButton(int sensorPin);
    void Initialize();
    void Update();
    void InterruptTriggered();

    void RegisterSingleTapHandler(TouchButtonHandler handler);
    void RegisterDoubleTapHandler(TouchButtonHandler handler);
    void RegisterHoldHandler(TouchButtonHandler handler);
    void RegisterTapAndHoldHandler(TouchButtonHandler handler);
    void RegisterTripleTapHandler(TouchButtonHandler handler);

    void TouchHoldTimeout();
    void TouchTimeout();
    void TouchPinChange();
};
