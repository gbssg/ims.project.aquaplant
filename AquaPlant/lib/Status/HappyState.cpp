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
    playEmoji(HAPPY);
};
void HappyState::ExecuteMD() {
    // No implementation for HappyState
};
void HappyState::ConfigureBooleans()
{
    setBooleans(1);
}
