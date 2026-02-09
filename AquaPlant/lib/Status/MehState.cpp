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
    lcdMeh();
};
void MehState::RenderOLED()
{
    playEmoji(MEH);
};
void MehState::ExecuteMD()
{
    // No implementation for MehState
    Serial.println("MehState: No MD action required.");
};
void MehState::ConfigureBooleans()
{
    setBooleans(1);
}
