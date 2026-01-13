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
bool waterAllowed = true;
bool screenCleared = false;

IState *statesArray[] = {
    new HappyState(),
    new MehState(),
    new SadState()};

IState *aktuellerZustand = nullptr;

// Fehler noch beheben.
void wateringState()
{
  int waterTime = 10;
  bool waterIt = true;
  int secondsPrevious = 0;
  int secondsPassed = 0;

  while (waterIt)
  {
    secondsPrevious = millis() / 1000;
    secondsPassed = millis() / 1000 - secondsPrevious;
    lcdWateringStateLoop();

    if (secondsPassed >= 1)
    {
      secondsPrevious = secondsPassed;
      waterTime--;

      if (waterTime <= 0)
      {
        waterIt = false;
      }
    }
  }
}

void normalState()
{
  lcdNormalStateLoop();

  moistureSensorLoop();

  WriteCharLoadingAnimation();

  int value = get_value();

  if (value <= 500)
  {
    state = 0;
    waterAllowed = true;
    screenCleared = false;
  }
  else if (value <= 700 && value > 500)
  {
    state = 1;
    waterAllowed = true;
    screenCleared = false;
  }
  else if (value > 700)
  {
    state = 2;
    if (waterAllowed)
    {
      if (!screenCleared)
      {
        ClearScreen();
        screenCleared = true;
      }
      wateringState();
      waterAllowed = false;
    }
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
