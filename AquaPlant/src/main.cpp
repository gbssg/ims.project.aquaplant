#include <Arduino.h>
#include <Wire.h>
#include "MS.h"
#include "MD.h"
#include "LCD.h"
#include "OLED.h"
#include "SCMD.h"
#include "SCMD_config.h"
#include "WP.h"
// Class
#include "IState.h"
#include "HappyState.h"
#include "MehState.h"
#include "SadState.h"

// Bemerkung: Ein paar Variabeln werden extern benutzt
int state = 0;
int previousTime = millis();
bool waterAllowed = true;
bool screenCleared = false;
bool loadedOnce = false;
bool setSadStateTime = true;
bool timerStartedDuration = false;
int previousTimeForDuration = 0;
int timeInSadState = 0;
int timeSinceLastWatering = 0;
int previousTimeForWatering = 0;
static SCMD myMD; // Objekt erstellen

// Alle drei States für das StrategyPattern
IState *statesArray[] = {
    new HappyState(),
    new MehState(),
    new SadState()};

// Pointer initialisieren
IState *aktuellerZustand = nullptr;

void StateSelection()
{

  lcdNormalStateLoop();

  moistureSensorLoop();

  WriteCharLoadingAnimation();

  int value = get_value();

  if (value <= 500)
  {
    state = 0;
  }
  else if (value <= 700 && value > 500)
  {
    state = 1;
  }
  else if (value > 700)
  {
    state = 2;
  }

  aktuellerZustand = statesArray[state];

  aktuellerZustand->RenderLCD();
  aktuellerZustand->RenderOLED();
  aktuellerZustand->ExecuteMD();
}

void setup()
{
  Serial.begin(115200);
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
  stateSelection();
}
