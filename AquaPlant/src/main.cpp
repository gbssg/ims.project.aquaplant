#include <Arduino.h>
#include <Wire.h>
#include "MS.h"
#include "MD.h"
#include "LCD.h"
#include "OLED.h"
#include "HappyState.h"
// Class
#include "IState.h"

int value = get_value();
int state = 0;

typedef void (*FunctionPointer)();
FunctionPointer statePointer = NULL;

void happyState()
{
  emojiHappy2();
  LCDHappy();
}

void mehState()
{
  emojiHappy2();
  LCDHappy();
  MDLoopMeh();
}

void sadState()
{
  emojiSad2();
  LCDSad();
  MDLoopSad();
}

FunctionPointer states[] =
    {
        happyState,
        mehState,
        sadState};

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

  statePointer = states[state];
  statePointer();
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
