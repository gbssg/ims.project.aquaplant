#include <Arduino.h>
#include <stdint.h>
#include "Wire.h"
#include "LCD.h"
#include "MS.h"

extern bool waterAllowed;
extern bool screenCleared;
extern bool loadedOnce;
extern bool setSadStateTime;
extern bool timerStartedDuration;

void setBooleans(int inputForBooleanGroup)
{
    if (inputForBooleanGroup == 1)
    {
        waterAllowed = true;
        screenCleared = false;
        loadedOnce = false;
        timerStartedDuration = false;
    }
    else if (inputForBooleanGroup == 2)
    {
        setSadStateTime = true;
    }
}