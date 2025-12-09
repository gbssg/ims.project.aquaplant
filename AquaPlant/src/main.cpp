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

int value = get_value();
int state = 0;

IState *statesArray[] = {
    new HappyState(),
    new MehState(),
    new SadState()};

IState *aktuellerZustand = nullptr;

void normalState()
{
  lcdNormalStateLoop();

  moistureSensorLoop();

  WriteCharLoadingAnimation();

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

void wateringState()
{
  lcdWateringStateLoop();
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
  wateringState();
}
