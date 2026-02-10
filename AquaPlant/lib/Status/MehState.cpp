#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
#include "WP.h"
// Class
#include "IState.h"
#include "MehState.h"

void MehState::RenderLCD()
{
    LCDMeh();
    setBooleans(1);
};
void MehState::RenderOLED()
{
    emojiMeh2();
    setBooleans(1);
};
void MehState::ExecuteMD()
{
    // No implementation for HappyState
    Serial.println("HappyState: No MD action required.");
};
