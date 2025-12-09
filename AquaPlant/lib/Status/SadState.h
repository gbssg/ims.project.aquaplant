#pragma once

#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
// Class
#include "IState.h"

class SadState : public IState
{
public:
    void RenderLCD()
    {
        LCDSad();
    };
    void RenderOLED()
    {
        emojiSad2();
    };
    void ExecuteMD() {
        // MDLoopSad();
    };
};