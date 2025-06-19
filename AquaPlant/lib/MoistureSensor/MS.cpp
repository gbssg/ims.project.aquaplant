#include "MS.h"
#include <Wire.h>
#include <Arduino.h>

char Command_Get_Value = 0x05; // Wert vom Status holen
char Command_LED_off = 0x00;   // LED aus
char Command_LED_on = 0x01;    // LED an
char qwiicAddress = 0x28;      // Moisture Sensor Addresse

unsigned long startMillisMSSetup = 0;
unsigned long startMillisMSLoop = 0;

uint16_t ADC_VALUE = 0; // Feuchtigkeitswert

int get_value()
{
    Wire.beginTransmission(qwiicAddress);
    Wire.write(Command_Get_Value); // command for status
    Wire.endTransmission();        // stop transmitting

    Wire.requestFrom((uint8_t)qwiicAddress, (uint8_t)2); // request 1 bytes from slave device qwiicAddress

    // Example Code
    while (Wire.available())
    {
        uint8_t ADC_VALUE_L = Wire.read();
        uint8_t ADC_VALUE_H = Wire.read();
        ADC_VALUE = ADC_VALUE_H;
        ADC_VALUE <<= 8;
        ADC_VALUE |= ADC_VALUE_L;
        Serial.print("ADC_VALUE:  ");
        Serial.println(ADC_VALUE);
    }
    uint16_t x = Wire.read();
    // Example Code
    int ADC_Wert = int(ADC_VALUE);
    Wire.println(ADC_VALUE);
    return ADC_Wert;
}

void moistureSensorLoop()
{
    if ((millis() - startMillisMSLoop) <= 1000)
    {
        get_value();
        ledOn();
    }
    else if ((millis() - startMillisMSLoop) <= 2000)
    {
        ledOff();
    }
    else
    {
        startMillisMSLoop = millis();
    }
}

void moistureSensorSetup()
{
    if ((millis() - startMillisMSSetup) <= 1000)
    {
        ledOn();
    }
    else
    {
        startMillisMSSetup = millis();
    }
}

void ledOn()
{
    Wire.beginTransmission(qwiicAddress);
    Wire.write(Command_LED_on);
    Wire.endTransmission();
}

void ledOff()
{
    Wire.beginTransmission(qwiicAddress);
    Wire.write(Command_LED_off);
    Wire.endTransmission();
}
