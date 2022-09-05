#include "stdint.h"
#include "application.h"

void randomColor(uint8_t* color)
{
    color[0] = random(256);
    color[1] = random(256);
    color[2] = random(256);   
}