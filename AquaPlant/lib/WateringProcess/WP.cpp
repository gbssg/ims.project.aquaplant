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

extern int previousTimeForDuration;
extern int previousTimeForWatering;
extern int timeSinceLastWatering;
extern int timeInSadState;
extern int previousTime;

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

// Seperater State innerhalb des SadSates, welches für die Bewässerung zuständig ist
void wateringState(int timeWithoutWater)
{

    int previousTime = millis();
    int waterTime = 15;
    // MD_On();

    while (millis() - previousTime < (waterTime * 1000))
    {
        lcdWateringStateLoop(timeWithoutWater);
    }
    // MD_Off();
}

// Vorgang um wateringState aufzurufen
void wateringLogic()
{
    if (!timerStartedDuration)
    {
        previousTimeForDuration = millis() / 1000;
        previousTimeForWatering = millis() / 1000;
        timerStartedDuration = true;
    }

    timeSinceLastWatering = millis() / 1000 - previousTimeForWatering;
    timeInSadState = millis() / 1000 - previousTimeForDuration;

    if (timeSinceLastWatering >= 30)
    {
        wateringState(timeInSadState);
        previousTimeForWatering = millis() / 1000;
    }

    if (loadedOnce)
    {
        if (waterAllowed)
        {
            if (!screenCleared)
            {
                ClearScreen();
                screenCleared = true;
                previousTime = millis();
            }
            BackGroundColor(75, 255, 255);
            wateringState(timeInSadState);
            waterAllowed = false;
        }
    }
    loadedOnce = true;
}