#pragma once

#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
// Class
#include "IState.h"

class HappyState : public IState
{
public:
    void RenderLCD();
    void RenderOLED();
    void ExecuteMD();
    void ConfigureBooleans();
};