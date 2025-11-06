#include <Arduino.h>
#include <Wire.h>
#include "MS.h"
#include "MD.h"
#include "LCD.h"
#include "OLED.h"

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  Wire.begin();
  moistureSensorSetup();
  lcdSetup();
  CreateCharSetup();
  oledSetup();
  MDSetup();
}

void loop()
{
  lcdLoop();

  moistureSensorLoop();

  WriteChar();

  if (get_value() <= 500)
  {
    emojiHappy2();
    LCDHappy();
  }
  else if (get_value() <= 700 && get_value() > 500)
  {
    emojiMeh2();
    LCDMeh();
    MDLoopMeh();
  }
  else if (get_value() > 700)
  {
    emojiSad2();
    LCDSad();
    MDLoopSad();
  }
}
