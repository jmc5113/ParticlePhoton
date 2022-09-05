#include "application.h"

class HighPowerLed
{
private:
    int mPwmPin;
    int mPwmValue;
    bool mEnabled;

public:
    HighPowerLed(int highPowerLedPin);

    void Initialize();
    void increaseBrightness();
    void decreaseBrightness();

    void toggleHighPowerLed();
};