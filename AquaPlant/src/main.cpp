#include <Arduino.h>
#include <Wire.h>
#include "MS.h"
#include "MD.h"
#include "LCD.h"
#include "OLED.h"

int TimeForMehStatus = 0;
bool StopMehStatus = false;
int TimeForHappyStatus = 0;
bool StopHappyStatus = false;

void stopWatchHappyStatus()
{
  if (!StopHappyStatus)
  {
    TimeForHappyStatus = millis();
    Serial.println("------------------");
    Serial.print("Time for Happy:");
    Serial.println(TimeForHappyStatus / 1000);
    Serial.println("------------------");
    StopHappyStatus = true;
  }
}

void stopWatchMehStatus()
{
  if (!StopMehStatus)
  {
    TimeForMehStatus = millis();
    Serial.println("------------------");
    Serial.print("Time for Meh:");
    Serial.println(TimeForMehStatus / 1000);
    Serial.println("------------------");
    StopMehStatus = true;
  }
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
