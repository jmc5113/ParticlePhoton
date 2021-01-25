// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

// Adafruit_NeoPixel Pixy1(1, D1, WS2811);

int numLeds = 16;
Adafruit_NeoPixel Pixy1(numLeds, D2, WS2812B);
Adafruit_NeoPixel Pixy2(numLeds, D3, WS2812B);

// Output PWM pin for high power led.
int highPowerLedEnPin = D0;

// Interrupt pins
int toggleLedPin = D4;
int decreaseBrightnessPin = D5;
int increaseBrightnessPin = D6;


int highPowerLedPwmValue = 245;
bool highPowerLedEnabled = false;

// Used to prevent the interrupts from firing many times in a row.
unsigned long interruptTime = 0;

void toggleLed()
{
    if(millis() - interruptTime < 500)
    {
        return;
    }
    interruptTime = millis();

    if(highPowerLedEnabled)
    {
        // Turn off led
        analogWrite(highPowerLedEnPin, 255, 200);
        highPowerLedEnabled = false;
    }
    else
    {
        // Set the PWM value back to where it was.
        analogWrite(highPowerLedEnPin, highPowerLedPwmValue, 200);
        highPowerLedEnabled = true;
    }

    //wait(.25);
}

void increaseBrightness()
{
    if(millis() - interruptTime < 500)
    {
        return;
    }
    interruptTime = millis();

    if(highPowerLedPwmValue >= 25)
    {
        highPowerLedPwmValue -= 25; 
    }
    else
    {
        highPowerLedPwmValue = 0;  
    }

    analogWrite(highPowerLedEnPin, highPowerLedPwmValue, 200);
    //wait(.25); 
}

void decreaseBrightness()
{
    if(millis() - interruptTime < 500)
    {
        return;
    } 
    interruptTime = millis();

    if(highPowerLedPwmValue <= 230)
    {
        highPowerLedPwmValue += 25; 
    }
    else
    {
        highPowerLedPwmValue = 255;    
    }

    analogWrite(highPowerLedEnPin, highPowerLedPwmValue, 200);
    //wait(.25);
}


void rainbow()
{
    if(millis() % 250 == 0)
    {
        for(int i = 0; i < numLeds; i++)
        {
            Pixy1.setPixelColor(i, 0xFF, 0x00, 0x00);
            Pixy2.setPixelColor(i, 0x00, 0xFF, 0x00);
        }
        Pixy1.show();
        Pixy2.show(); 
    }
}

#define NUM_COLORS 6
uint32_t colors[NUM_COLORS] = 
{
    Pixy1.Color(0xFF, 0x00, 0x00), // Red
    Pixy1.Color(0xFF, 0xFF, 0x00), // Yellow
    Pixy1.Color(0xFF, 0x00, 0xFF), // Purple
    Pixy1.Color(0x00, 0xFF, 0x00), // Green
    Pixy1.Color(0xFF, 0xFF, 0xFF), // White
    Pixy1.Color(0x00, 0x00, 0xFF), // Blue
};

// uint32_t color = 0;
int colorCounter = 0;
int iterationCounter = 0;
void colorChaseSymmetric()
{
        int n = iterationCounter % numLeds;
        if(n == 0)
        {
            colorCounter++;
            if(colorCounter == 6)
            {
                colorCounter = 0;
            }
        }
        // for(int i = 0; i < n; i++)
        // {
            Pixy1.setPixelColor(n, colors[colorCounter]);
            Pixy2.setPixelColor(n, colors[colorCounter]);
        // }
        Pixy1.show();
        Pixy2.show(); 

        iterationCounter++;
}


Timer timer(500, colorChaseSymmetric);
int startTime = 0;

void setup() {

    pinMode(highPowerLedEnPin, OUTPUT);

    pinMode(toggleLedPin, INPUT_PULLDOWN);
    pinMode(decreaseBrightnessPin, INPUT_PULLDOWN);
    pinMode(increaseBrightnessPin, INPUT_PULLDOWN);

    attachInterrupt(toggleLedPin, toggleLed, RISING);
    attachInterrupt(decreaseBrightnessPin, decreaseBrightness, RISING);
    attachInterrupt(increaseBrightnessPin, increaseBrightness, RISING);

    analogWrite(highPowerLedEnPin, highPowerLedPwmValue, 200);

    Pixy1.begin();
    Pixy2.begin();
    timer.start();
}

void loop() {

}