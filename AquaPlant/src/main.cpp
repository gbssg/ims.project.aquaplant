#include <Arduino.h>
#include <Wire.h>
#include "MS.h"
#include "MD.h"
#include "LCD.h"
#include "OLED.h"

int timeForMehStatus = 0;
int timeForHappyStatus = 0;

void stopWatchHappyStatus()
{
  timeForHappyStatus = millis();
  Serial.println("------------------");
  Serial.println(timeForHappyStatus);
  Serial.println("------------------");
}

void stopWatchMehStatus()
{
  timeForHappyStatus = millis();
  Serial.println("------------------");
  Serial.println(timeForMehStatus);
  Serial.println("------------------");
}

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
    stopWatchHappyStatus();
  }
  else if (get_value() <= 700 && get_value() > 500)
  {
    emojiMeh2();
    LCDMeh();
    stopWatchMehStatus();
  }
  else if (get_value() > 700)
  {
    emojiSad2();
    LCDSad();
  }
}
