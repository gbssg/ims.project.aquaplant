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
};
void HappyState::RenderOLED()
{
    happyEmojiAnimation();
};
void HappyState::ExecuteMD()
{
    // No implementation for HappyState
    Serial.println("HappyState: No MD action required.");
};
void HappyState::ConfigureBooleans()
{
    setBooleans(1);
}
