#include "application.h"

typedef void (*TouchButtonHandler)();

class TouchButton
{
private:
    int mTouchPin;
    bool mTouchHold;
    bool mTouchTap;
    bool mTouchDoubleTap;
    Timer mTouchHoldTimer;
    Timer mTouchTimeoutTimer;

    TouchButtonHandler mSingleTapHandler;
    TouchButtonHandler mDoubleTapHandler;
    TouchButtonHandler mHoldHandler;
    TouchButtonHandler mTapAndHoldHandler;
    
public:
    TouchButton(int sensorPin);
    void Initialize();

    void RegisterSingleTapHandler(TouchButtonHandler singleTapHandler);
    void RegisterDoubleTapHandler(TouchButtonHandler doubleTapHandler);
    void RegisterHoldHandler(TouchButtonHandler holdHandler);
    void RegisterTapAndHoldHandler(TouchButtonHandler tapAndHoldHandler);

    void TouchHoldTimeout();
    void TouchTimeout();
    void TouchPinChange();
};
