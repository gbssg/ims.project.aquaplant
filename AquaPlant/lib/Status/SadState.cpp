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
};
void SadState::RenderOLED()
{
    playEmoji(SAD);
};
void SadState::ExecuteMD()
{
    wateringLogic();
};
void SadState::ConfigureBooleans()
{
    setBooleans(2);
}
