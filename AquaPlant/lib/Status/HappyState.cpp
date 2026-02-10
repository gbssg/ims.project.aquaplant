#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
#include "WP.h"
// Class
#include "IState.h"
#include "HappyState.h"

void HappyState::RenderLCD()
{
    lcdHappy();
    setBooleans(1);
};
void HappyState::RenderOLED()
{
    emojiHappy2();
    setBooleans(1);
};
void HappyState::ExecuteMD()
{
    // No implementation for HappyState
    Serial.println("HappyState: No MD action required.");
};
