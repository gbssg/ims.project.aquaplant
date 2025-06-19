#include <SerLCD.h> // LCD Bilbiothek
#include <Wire.h>
#include <MS.h>
#include "LCD.h"

static SerLCD lcd; // Initialisierung der Bibliothek mit der default I2C addresse 0x72
unsigned long startMillislcdLoop = 0;

void lcdSetup()
{
  lcd.begin(Wire);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(5);
}

void lcdLoop()
{
  if ((millis() - startMillislcdLoop) <= 5000)
  {
    lcd.setCursor(0, 0);
    lcd.print("Messwert:");
    lcd.print(get_value());
  }
  else
  {
    startMillislcdLoop = millis();
    Serial.println("Clear");
    lcd.clear();
  }
}

void statusGood()
{
  lcd.setCursor(0, 1);
  lcd.print("Wunderbar!");
}

void statusMeh()
{
  lcd.setCursor(0, 1);
  lcd.print("Ganz okey...");
}

void statusBad()
{
  lcd.setCursor(0, 1);
  lcd.print("Gib mir Wasser!");
}
