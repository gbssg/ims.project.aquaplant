#include <Arduino.h>
#include <Wire.h>
#include "MS.h"
#include "MD.h"
#include "LCD.h"
#include "OLED.h"
// Class
#include "IState.h"
#include "HappyState.h"
#include "MehState.h"
#include "SadState.h"

int state = 0;
int previousTime = millis();
int timeWithoutWatering = 0;
bool waterAllowed = true;
bool screenCleared = false;
bool loadedOnce = false;
bool setSadStateTime = true;

IState *statesArray[] = {
    new HappyState(),
    new MehState(),
    new SadState()};

IState *aktuellerZustand = nullptr;

// Fehler noch beheben.
void wateringState()
{
  int previousTime = millis();
  int waterTime = 15;
  bool waterIt = true;

  while (millis() - previousTime < (waterTime * 1000))
  {
    lcdWateringStateLoop();
  }
}

void normalState()
{

  lcdNormalStateLoop();

  moistureSensorLoop();

  WriteCharLoadingAnimation();

  int value = get_value();
  int timeInSadState = 0;

  if (value <= 500)
  {
    state = 0;
    waterAllowed = true;
    screenCleared = false;
    loadedOnce = false;

    if (setSadStateTime)
    {
      timeInSadState = millis() / 1000 - previousTime / 1000;
      setSadStateTime = false;
    }
    Serial.println(timeInSadState);
  }
  else if (value <= 700 && value > 500)
  {
    state = 1;
    waterAllowed = true;
    screenCleared = false;
    loadedOnce = false;

    if (setSadStateTime)
    {
      timeInSadState = millis() / 1000 - previousTime / 1000;
      setSadStateTime = false;
    }
    Serial.println(timeInSadState);
  }
  else if (value > 700)
  {
    state = 2;
    setSadStateTime = true;

    if (loadedOnce)
    {
      if (waterAllowed)
      {
        if (!screenCleared)
        {
          ClearScreen();
          screenCleared = true;
        }
        wateringState();
        waterAllowed = false;
        previousTime = millis();
      }
    }
    loadedOnce = true;
  }

  aktuellerZustand = statesArray[state];

  aktuellerZustand->RenderLCD();
  aktuellerZustand->RenderOLED();
  aktuellerZustand->ExecuteMD();
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  Wire.begin();
  moistureSensorSetup();
  lcdSetup();
  createCharSetupRainDrop();
  createCharSetupClock();
  CreateCharSetupBackslash();
  CreateCharSetup();
  oledSetup();
  MDSetup();
}

void loop()
{
  normalState();
}
