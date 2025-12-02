#include <Arduino.h>
#include <Wire.h>
#include "MS.h"
#include "MD.h"
#include "LCD.h"
#include "OLED.h"

int value = get_value();

typedef void (*FunctionPointer)();
FunctionPointer emojiPointer = NULL;
FunctionPointer LCDPointer = NULL;

FunctionPointer emojiMethods[] =
    {
        emojiHappy2,
        emojiMeh2,
        emojiSad2};

FunctionPointer LCDMethods[] =
    {
        LCDHappy,
        LCDMeh,
        LCDSad};

void normalState()
{
  lcdNormalStateLoop();

  moistureSensorLoop();

  WriteCharLoadingAnimation();

  if (value <= 500)
  {
    emojiPointer = emojiMethods[0];
    LCDPointer = LCDMethods[0];
  }
  else if (value <= 700 && value > 500)
  {
    emojiPointer = emojiMethods[1];
    LCDPointer = LCDMethods[1];

    MDLoopMeh();
  }
  else if (value > 700)
  {
    emojiPointer = emojiMethods[2];
    LCDPointer = LCDMethods[2];

    MDLoopSad();
  }

  emojiPointer();
  LCDPointer();
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
  CreateCharSetup();
  oledSetup();
  MDSetup();
}

void loop()
{
  wateringState();
}
