#include <SerLCD.h>
#include <Wire.h>
#include <MS.h>
#include "LCD.h"
#include "MD.h"
#include "OLED.h"

static SerLCD lcd;
unsigned long startMillislcdLoop = 0;
int startMillisLoadingLoop = 0;
int i = 1;
int messwert = 0;

int startMillisWateringState = 0;
int timeWateringStateStandard = 15;
int cycle = 1;
int timeWateringState = timeWateringState;

boolean isWatering = true;

// Grundeinstellungen
void lcdSetup()
{
  lcd.begin(Wire);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(5);
}

// Datenanzeige des LCDs, ausserhalb des Bewässerungszustandes
void lcdNormalStateLoop()
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

// Datenanzeige des LCDs, während die Pumpe Läuft
void lcdWateringStateLoop(int timeWithoutWater)
{
  messwert = 100 - (100 / (double)1023 * get_value());

  if ((millis() - startMillisWateringState) >= 1000)
  {

    if (timeWateringState <= 0)
    {
      timeWateringState = timeWateringStateStandard;
      isWatering = false;
    }
    else
    {
      if (timeWateringState == 14)
      {
        lcd.clear();
      }
      backGroundColor(75, 255, 255);

      startMillisWateringState = millis();

      lcd.setCursor(0, 0);
      writeCharRainDrop();

      lcd.setCursor(1, 0);
      lcd.print(":");

      lcd.setCursor(2, 0);
      lcd.print(messwert);

      lcd.setCursor(4, 0);
      lcd.print("%");

      lcd.setCursor(8, 0);
      writeCharClock();

      lcd.setCursor(9, 0);
      lcd.print(":");

      // Um den Wechsel von zweistellige zu einstellige Sekunden aufzuräumen
      if (timeWateringState == 10)
      {
        lcd.clear();
      }

      if (timeWateringState > 3600)
      {
        lcd.print(timeWateringState / 60 / 60);
        timeWateringState--;
        lcd.print("h");
      }
      else if (timeWateringState > 60)
      {
        lcd.print(timeWateringState / 60);
        timeWateringState--;
        lcd.print("m");
      }
      else if (timeWateringState <= 60)
      {
        lcd.print(timeWateringState);
        timeWateringState--;
        lcd.print("s");
      }

      lcd.setCursor(0, 1);
      writeCharClock();

      lcd.setCursor(1, 1);
      writeCharBackslash();
      writeCharRainDrop();
      lcd.print(":");

      Serial.print("time without water: ");
      Serial.println(timeWithoutWater);
      if (timeWithoutWater > 60)
      {
        lcd.print(timeWithoutWater / 60);
        if (timeWithoutWater / 60 == i)
        {
          cycle++;
          i++;
        }
        lcd.print("m");
        lcd.print(":");
        lcd.print(timeWithoutWater - 60 * cycle);
        lcd.print("s");
      }
      else if (timeWithoutWater <= 60)
      {
        lcd.print(timeWithoutWater);
        lcd.print("s");
      }
    }
  }
}

// Nachrichten, welche je nach Zustand angezeigt werden
// Überarbeiten!
/*
Eventuell könnte man im SadState die Zeit ohne Wasser aufzeigen
*/

void lcdHappy()
{
  lcd.setCursor(0, 1);
  lcd.print("Wunderbar!     ");
  backGroundColor(255, 255, 255);
}

void lcdMeh()
{
  lcd.setCursor(0, 1);
  lcd.print("Ganz okey...   ");
  backGroundColor(255, 255, 255);
}

void lcdSad()
{
  lcd.setCursor(0, 1);
  lcd.print("Gib mir Wasser!");
  backGroundColor(255, 255, 255);
}

// Animation zur Überprüfung der FPS
void createCharSetup()
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

// Regentropfen char Vorlage
void createCharSetupRainDrop()
{
  byte raindrop[8] = {
      B00000,
      B00010,
      B00110,
      B01010,
      B10001,
      B10001,
      B10001,
      B01110};

  lcd.createChar(5, raindrop);
}

// Wanduhr char Vorlage
void createCharSetupClock()
{
  byte clock[8] = {
      B01110,
      B10001,
      B10011,
      B10101,
      B10101,
      B10001,
      B10001,
      B01110};

  lcd.createChar(6, clock);
}

// Backslash char Vorlage
void createCharSetupBackslash()
{
  byte backslash[8] = {
      B00000,
      B00001,
      B00010,
      B00100,
      B01000,
      B10000,
      B00000,
      B00000};

  lcd.createChar(7, backslash);
}

// Zyklus der Animation ausgeben
void writeCharLoadingAnimation()
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

// Regentropfen ausgeben
void writeCharRainDrop()
{
  lcd.writeChar(5);
}

// Wanduhr ausgeben
void writeCharClock()
{
  lcd.writeChar(6);
}

// Backslash ausgeben
void writeCharBackslash()
{
  lcd.writeChar(7);
}

// Troubleshooting für den Motordriver + Pumpe
void MDTesting()
{
  if (getStatus() == 1)
  {
    lcd.clear();
    lcd.println("Motor is ON");
  }
  else if (getStatus() == 0)
  {
    lcd.clear();
    lcd.println("Motor is OFF");
  }
  else
  {
    lcd.clear();
    Serial.print("Error");
  }
  lcd.println(getLevel());
}

// Bildschirm leeren globally
void clearScreen()
{
  lcd.clear();
}

// Hintergrundfarbe einstellen im main.cpp
void backGroundColor(int red, int green, int blue)
{
  lcd.setFastBacklight(red, green, blue);
}
