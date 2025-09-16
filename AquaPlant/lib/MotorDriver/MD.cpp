#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h"
#include "Wire.h"
#include "LCD.h"

static SCMD myMD; // Objekt erstellen
SCMDDiagnostics Diagnostics;

uint8_t MDAdress = 0x5D; // 0x5D
uint8_t motorNum = 0;    // 0-33  Addressen verfügbar|Pumpe => 0
uint8_t direction = 1;   // 0/1   Vorwärts
uint8_t level = 80;      // 0-255 Geschwindigkeit | 80-255

int status = 10;

unsigned long startMillisMD = 0;

void MDSetup()
{

    // Settings
    myMD.settings.commInterface = I2C_MODE;
    myMD.settings.I2CAddress = MDAdress;

    myMD.begin(); // Einstellungen übernehmen

    while (myMD.begin() != 0xA9) // Wait until a valid ID word is returned
    {
        Serial.println("ID mismatch, trying again");
        delay(500);
    }
    Serial.println("ID matches");
}

void SetStatus(int NewStatus)
{
    status = NewStatus;
    Serial.print("\nStatus changed to: ");
    Serial.print(status);
    Serial.print("\n");
}

int GetStatus()
{
    Serial.print("Received Status: ");
    Serial.print(status);
    Serial.print("\n");

    return status;
}

int GetMotorNum()
{
    return motorNum;
}

int GetLevel()
{
    return level;
}

void MDLoop()
{
    if (myMD.ready())
    {
        if (!myMD.busy())
        {
            myMD.enable();
            for (level; level <= 200; level += 10)
            {
                myMD.setDrive(motorNum, direction, level);
                // Serial.println("Motor deactivated");
                SetStatus(0);
                MDTesting();
                delay(1000);
                myMD.setDrive(motorNum, direction, level);
                // Serial.println("Motor running");
                SetStatus(1);
                MDTesting();
                delay(1000);
            }
        }
    }
}

void MDLoopMeh()
{
    level = 125;
    if (myMD.ready())
    {
        if (!myMD.busy())
        {
            myMD.enable();
            myMD.setDrive(motorNum, direction, level);
            // 30 Sekunden warten, damit die Zustände nicht ständig hin und her wechseln
            if ((millis() - startMillisMD) <= 30000)
            {
                myMD.disable();
                myMD.reset();
            }
            else
            {
                startMillisMD = millis();
            }
        }
    }
}

void MDLoopSad()
{
    level = 255;
    if (myMD.ready())
    {
        if (!myMD.busy())
        {
            myMD.enable();
            myMD.setDrive(motorNum, direction, level);
            delay(2000);
            myMD.disable();
            myMD.reset();
        }
    }
}

// Under Construction
void getDiagnostics()
{
    myMD.getDiagnostics(Diagnostics);
}