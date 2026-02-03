#include <Arduino.h>
#include "OLED.h"
#include "LCD.h"
#include "MD.h"
// Class
#include "IState.h"
#include "MehState.h"

void MehState::RenderLCD()
{
    LCDMeh();
};
void MehState::RenderOLED()
{
    emojiMeh2();
};
void MehState::ExecuteMD()
{
    // No implementation for HappyState
    Serial.println("HappyState: No MD action required.");
};
