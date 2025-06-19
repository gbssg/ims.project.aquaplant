#include <Arduino.h>
#include <Wire.h>
#include <MS.h>
#include <LCD.h>
#include <OLED.h>

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  Wire.begin();

  oledSetup();

  lcdSetup();

  moistureSensorSetup();
}

void loop()
{

  lcdLoop();

  moistureSensorLoop();

  if (get_value() <= 500)
  {
    emojiHappy();
    statusGood();
  }
  else if (get_value() <= 700 && get_value() > 500)
  {
    emojiMeh();
    statusMeh();
  }
  else if (get_value() > 700)
  {
    emojiSad();
    statusBad();
  }
}
