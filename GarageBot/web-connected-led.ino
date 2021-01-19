// -----------------------------------
// Controlling LEDs over the Internet
// -----------------------------------

// First, let's create our "shorthand" for the pins
// Same as in the Blink an LED example:
// led1 is D0, led2 is D7

int led1 = D0;
int led2 = D7;
int opIn = A0;
int doorStatus = 0;

void readOpticalIn()
{
    int val = analogRead(opIn);
    float volts = val / 4095.0 * 3.3;
    
    Serial.print(val);
    Serial.print(" : ");
    Serial.println(volts);
    
}

Timer readTimer(50, readOpticalIn);


void setup()
{
    Serial.begin(115200);
    Serial.println("Hello GarageBot");

    // Here's the pin configuration, same as last time
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
   
    // OPB745 LED 2V
    pinMode(DAC1, OUTPUT);
    analogWrite(DAC1, 2482);
   
    // OPB745 Read Voltage
    pinMode(opIn, INPUT_PULLDOWN);

    // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
    Particle.function("led", ledToggle);
    Particle.variable("doorStatus", doorStatus);

    // For good measure, let's also make sure both LEDs are off when we start:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    
    //Start Timer eventually this will move to start when the door is opening 
    readTimer.start();
}


// Last time, we wanted to continously blink the LED on and off
// Since we're waiting for input through the cloud this time,
// we don't actually need to put anything in the loop

void loop()
{
   
}

// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Particle.function earlier.


int ledToggle(String command) {
    /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

    if (command=="on") {
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        doorStatus = 100;
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        doorStatus = 0;
        return 0;
    }
    else {
        return -1;
    }
}

