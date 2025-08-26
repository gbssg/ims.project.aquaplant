#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h"
#include "Wire.h"

static SCMD myMD; // Objekt erstellen
SCMDDiagnostics Diagnostics;

uint8_t MDAdress = 0x5D;
uint8_t motorNum = 1;  // 0-33  Addressen verfügbar
uint8_t direction = 1; // 0/1   Vorwärts
uint8_t level = 255;   // 0-255 Geschwindigkeit

void MDSetup()
{
    Serial.begin(9600);

    // Settings
    myMD.settings.commInterface = I2C_MODE;
    myMD.settings.I2CAddress = MDAdress;

    myMD.begin(); // Einstellungen übernehmen
}

void MDLoop()
{
    if (myMD.ready())
    {
        if (!myMD.busy())
        {
            myMD.enable();
            myMD.setDrive(motorNum, direction, level);
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