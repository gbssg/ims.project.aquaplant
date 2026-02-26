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
void wateringProcess(int timeWithoutWater)
{

    int previousTime = millis();
    int waterDuration = 0;
    // Bewässerungsdauer
    int waterTime = 15;
    // MD_On();

    while (millis() - previousTime < (waterTime * 1000))
    {
        Serial.print("Duration:");
        Serial.println(millis() - previousTime);
        waterDuration = millis() - previousTime;

        wateringFrame();
        lcdWateringStateLoop(timeWithoutWater, waterDuration);
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
        wateringProcess(timeInSadState);
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
        wateringProcess(timeInSadState);
        waterAllowed = false;
    }
    loadedOnce = true;
}