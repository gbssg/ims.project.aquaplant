#pragma once

#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
// Class
#include "IState.h"

class MehState : public State
{
public:
    void RenderLCD()
    {
        LCDMeh();
    };
    void RenderOLED()
    {
        emojiMeh2();
    };
    void ExecuteMD()
    {
        MDLoopMeh();
    };
};