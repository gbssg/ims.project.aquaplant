#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
// Class
#include "IState.h"
#include "HappyState.h"

void HappyState::RenderLCD()
{
    LCDHappy();
};
void HappyState::RenderOLED()
{
    emojiHappy2();
};
void HappyState::ExecuteMD()
{
    // No implementation for HappyState
    Serial.println("HappyState: No MD action required.");
};
