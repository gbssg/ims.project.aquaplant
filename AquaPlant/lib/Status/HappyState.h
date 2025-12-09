#pragma once

#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
// Class
#include "IState.h"

class HappyState : public State
{
public:
    void RenderLCD()
    {
        LCDHappy();
    };
    void RenderOLED()
    {
        emojiHappy2();
    };
    void ExecuteMD()
    {
        // No implementation for HappyState
        Serial.println("HappyState: No MD action required.");
    };
};