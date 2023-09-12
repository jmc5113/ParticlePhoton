#pragma once

#include "stdint.h"
#include "application.h"

//////////
// colors
/////////
// {0xFF, 0x00, 0x00}, // Red
// {0xFF, 0x5F, 0x00}, // Red-Orange
// {0xFF, 0x7F, 0x00}, // Orange
// {0xFF, 0xFF, 0x00}, // Yellow
// {0x00, 0xFF, 0x00}, // Green
// {0x00, 0x3F, 0xFF}, // Light Blue
// {0x00, 0xFF, 0xFF}, // Medium Blue
// {0x00, 0x00, 0xFF}, // Blue
// {0xFF, 0x00, 0xFF}, // Purple
// {0xFF, 0x50, 0x7F}, // Light Pink
// {0xFF, 0x00, 0x7F}, // Pink
// {0xFF, 0xFF, 0xFF}, // White
// {0x00, 0x00, 0x00}, // Dark

extern uint8_t g_colorBlack[3];
extern uint8_t g_colorRedOrange[3];
extern uint8_t g_colorOrange[3];
extern uint8_t g_colorYellow[3];
extern uint8_t g_colorGreen[3];
extern uint8_t g_colorLightBlue[3];
extern uint8_t g_colorMediumBlue[3];
extern uint8_t g_colorPurple[3];
extern uint8_t g_colorLightPink[3];
extern uint8_t g_colorPink[3];
extern uint8_t g_colorWhite[3];


void randomColor(uint8_t* color);