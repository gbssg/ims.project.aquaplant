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

  CreateCharSetup();
}

void loop()
{
  lcdLoop();

  moistureSensorLoop();

  WriteChar();

  if (get_value() <= 500)
  {
    emojiHappy2();
    statusGood();
  }
  else if (get_value() <= 700 && get_value() > 500)
  {
    emojiMeh2();
    statusMeh();
  }
  else if (get_value() > 700)
  {
    emojiSad2();
    statusBad();
  }
}
