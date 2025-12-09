#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
// Class
#include "IState.h"
#include "SadState.h"

void SadState::RenderLCD()
{
    LCDSad();
};
void SadState::RenderOLED()
{
    emojiSad2();
};
void SadState::ExecuteMD() {
    // MDLoopSad();
};
