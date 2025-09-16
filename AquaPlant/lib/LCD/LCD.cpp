#include <SerLCD.h>
#include <Wire.h>
#include <MS.h>
#include "LCD.h"
#include "MD.h"

static SerLCD lcd;
unsigned long startMillislcdLoop = 0;
int startMillisLoadingLoop = 0;
int i = 0;
int messwert = 0;

// Grundeinstellungen
void lcdSetup()
{
  lcd.begin(Wire);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(5);
}

// Datenanzeige des LCDs
void lcdLoop()
{
  if ((millis() - startMillislcdLoop) <= 5000)
  {
    messwert = 100 - (100 / (double)1023 * get_value());
    lcd.setCursor(0, 0);

    if (messwert < 10)
    {
      lcd.print("Messwert:     ");
      lcd.print(messwert);
      lcd.print("%");
    }
    else if (messwert < 100)
    {
      lcd.print("Messwert:    ");
      lcd.print(messwert);
      lcd.print("%");
    }
    else if (messwert < 1000)
    {
      lcd.print("Messwert:   ");
      lcd.print(messwert);
      lcd.print("%");
    }
    else if (messwert < 10000)
    {
      lcd.print("Messwert:   ");
      lcd.print(messwert);
    }
    else
    {
      lcd.print("Messwert:  ");
      lcd.print(messwert);
    }
  }
  else
  {
    startMillislcdLoop = millis();
  }
}

// Nachrichten, welche je nach Zustand angezeigt werden
// Überarbeiten!
void LCDHappy()
{
  lcd.setCursor(0, 1);
  lcd.print("Wunderbar!     ");
}

void LCDMeh()
{
  lcd.setCursor(0, 1);
  lcd.print("Ganz okey...   ");
}

void LCDSad()
{
  lcd.setCursor(0, 1);
  lcd.print("Gib mir Wasser!");
}

// Animation zur Überprüfung der FPS
void CreateCharSetup()
{
  byte circle1[8] =
      {
          B00000,
          B00000,
          B00000,
          B10001,
          B10001,
          B00000,
          B00000,
          B00000,
      };
  byte circle2[8] =
      {
          B00000,
          B00000,
          B00010,
          B00001,
          B10000,
          B01000,
          B00000,
          B00000,
      };
  byte circle3[8] =
      {
          B00000,
          B00000,
          B00110,
          B00000,
          B00000,
          B01100,
          B00000,
          B00000,

      };
  byte circle4[8] =
      {
          B00000,
          B00000,
          B01100,
          B00000,
          B00000,
          B00110,
          B00000,
          B00000,
      };

  byte circle5[8] =
      {
          B00000,
          B00000,
          B01000,
          B10000,
          B00001,
          B00010,
          B00000,
          B00000,
      };

  lcd.createChar(0, circle1);
  lcd.createChar(1, circle2);
  lcd.createChar(2, circle3);
  lcd.createChar(3, circle4);
  lcd.createChar(4, circle5);
}

// Zyklus der Animation
void WriteChar()
{
  lcd.setCursor(15, 1);
  if ((millis() - startMillisLoadingLoop) <= 500)
  {
    lcd.writeChar(i);
    i++;
    if (i > 4)
    {
      i = 0;
    }
  }
  else
  {
    startMillisLoadingLoop = millis();
  }
}

void MDTesting()
{
  if (GetStatus() == 1)
  {
    lcd.clear();
    lcd.println("Motor is ON");
  }
  else if (GetStatus() == 0)
  {
    lcd.clear();
    lcd.println("Motor is OFF");
  }
  else
  {
    lcd.clear();
    Serial.print("Error");
  }
  lcd.println(GetLevel());
}

void ClearScreen()
{
  lcd.clear();
}
