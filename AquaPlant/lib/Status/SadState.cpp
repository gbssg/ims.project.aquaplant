#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
#include "WP.h"
// Class
#include "IState.h"
#include "SadState.h"

void SadState::RenderLCD()
{
    lcdSad();
    setBooleans(2);
};
void SadState::RenderOLED()
{
    emojiSad2();
    setBooleans(2);
};
void SadState::ExecuteMD()
{
    wateringLogic();
};
