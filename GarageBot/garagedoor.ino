//
// Garage Door Opener
//

enum {
    DOOR_UNKNOWN,
    DOOR_NOT_MOVING,
    DOOR_OPENING,
    DOOR_OPEN,
    DOOR_CLOSING,
    DOOR_CLOSED
};

// Pin declarations
int LED = D7;
int pinA = D0;
int pinB = D1;

bool isOn = false;
bool isOpen = false;
bool isClockwise = false;
int openDistance = 0;
int previousOpenDistance = 0;

int doorStatus = DOOR_UNKNOWN;
bool publishDoorStatus = false;

Timer movementTimeout(1000, doorStopped, true);
// Timer bounceTimeout(2000, publishDirection, true);

void doorStopped() 
{
    movementTimeout.stopFromISR();

    if(openDistance < 25)
    {
        doorStatus = DOOR_CLOSED;    
    }
    else
    {
        doorStatus = DOOR_OPEN;
    }
    
    // publishDoorStatus();
    publishDoorStatus = true;
    previousOpenDistance = openDistance;
}

void toggleDoorOpener()
{
    digitalWrite(LED, 1);
    delay(500);
    digitalWrite(LED, 0);
}

// Cloud functions must return int and take one String
int open(String extra) {
    toggleDoorOpener();
    
    if(doorStatus == DOOR_OPENING || doorStatus == DOOR_CLOSING)
    {
        return doorStatus;
    }
    
    return DOOR_NOT_MOVING;
}

void publishDirection()
{
    publishDoorStatus = true;
}

// Code for the rotary encoder to read the direction and the door open distance count
void pinBRise() {
    if (digitalRead(pinA) == HIGH)
    {
        isClockwise = true;
        doorStatus = DOOR_CLOSING;
        openDistance--;
    }
    else
    {
        isClockwise = false;
        doorStatus = DOOR_OPENING;
        openDistance++;
    }
    
    if(previousOpenDistance + 25 == openDistance ||
       previousOpenDistance - 25 == openDistance)
    {
        publishDoorStatus = true;
    }
    
    movementTimeout.resetFromISR();
}

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    
    attachInterrupt(pinB, pinBRise, RISING);
    
    Particle.variable("openDistance", openDistance);
    Particle.variable("doorStatus", doorStatus);
    Particle.function("open", open);
    
    // movementTimeout.start();
}


void loop() {
    
    if(publishDoorStatus)
    {
        publishDoorStatus = false;
        switch (doorStatus)
        {
            case DOOR_UNKNOWN:
                Particle.publish("Door Status", "Unknown");
                break;
            case DOOR_OPENING: 
                Particle.publish("Door Status", "Opening");
                break;
            case DOOR_OPEN: 
                Particle.publish("Door Status", "Open");
                break;
            case DOOR_CLOSING: 
                Particle.publish("Door Status", "Closing");
                break;
            case DOOR_CLOSED: 
                Particle.publish("Door Status", "Closed");
                break;
        }
    }
}