#include <Arduino.h>
#include <stdint.h>
#include "Wire.h"
#include "LCD.h"
#include "OLED.h"
#include "MS.h"

// Booleans
extern bool waterAllowed;
extern bool screenCleared;
extern bool loadedOnce;
extern bool setSadStateTime;
extern bool timerStartedDuration;

// Zeitstempeln
extern int lastTimeInSadState;
extern int lastTimeWatering;
extern int timeSinceLastWatering;
extern int timeInSadState;
extern int previousTime;

// Anpassungsfähige Variablen
extern int timeForNextWatering;
extern int waterTime;

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

// Seperater Prozess innerhalb der Wateringlogic, welches für die Bewässerung zuständig ist.
void wateringProcess(int timeWithoutWater, int effectiveWaterTime)
{

    int previousTime = millis();
    int waterDuration = 0;

    // MD_On();

    while (millis() - previousTime < (effectiveWaterTime * 1000))
    {
        waterDuration = millis() - previousTime;

        wateringFrame();
        lcdWateringStateLoop(timeWithoutWater, waterDuration, effectiveWaterTime);
    }
    // MD_Off();
}

// Logik hinter der Bewässerung
void wateringLogic()
{
    if (!timerStartedDuration)
    {
        lastTimeInSadState = millis() / 1000;
        lastTimeWatering = millis() / 1000;
        timerStartedDuration = true;
    }

    timeSinceLastWatering = millis() / 1000 - lastTimeWatering;
    timeInSadState = millis() / 1000 - lastTimeInSadState;

    if (timeSinceLastWatering >= timeForNextWatering)
    {
        wateringProcess(timeInSadState, waterTime);
        lastTimeWatering = millis() / 1000;
    }

    if (loadedOnce && waterAllowed)
    {
        if (!screenCleared)
        {
            clearScreen();
            screenCleared = true;
            previousTime = millis();
        }
        backGroundColor(75, 255, 255);
        wateringProcess(timeInSadState, waterTime);
        waterAllowed = false;
    }
    loadedOnce = true;
}