#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_5x7.h>
#include "OLED.h"

static Qwiic1in3OLED myOLED;
unsigned long startMillisEmoji = 0;
int width = myOLED.getWidth();
int height = myOLED.getHeight();

void oledSetup()
{
    Serial.println("OLED Setup");
    myOLED.begin();
    myOLED.flipHorizontal(true);
    myOLED.flipVertical(true);
    myOLED.text(0, 0, "OLED Loading...");
    myOLED.display();
    delay(1000);

    Serial.println("OLED Erase");
    myOLED.erase();

    Serial.println("Setting up display...");
    Serial.print("Display width/heigth: ");
    Serial.println(String(myOLED.getWidth()) + "/" + String(myOLED.getHeight()));
    myOLED.setFont(QW_FONT_5X7);
}

void emojiMeh()
{
    int widthLine = 0;
    int heightLine = 0;

    myOLED.erase();

    for (int i = 0; i <= 12; i++)
    {
        myOLED.text(widthLine + 32, 3, "\xC3");
        myOLED.text(widthLine + 32, 47, "\xC3");
        widthLine = widthLine + 5;
    }
    for (int ii = 0; ii <= 6; ii++)
    {
        myOLED.text(29, 8 + heightLine, "\xB2");
        myOLED.text(93, 8 + heightLine, "\xB2");
        heightLine = heightLine + 6;
    }

    myOLED.text(49, 18, "O");
    myOLED.text(75, 18, "O");

    widthLine = 0;

    for (int j = 0; j <= 5; j++)
    {
        myOLED.text(50 + widthLine, 37, "\xC3");
        widthLine = widthLine + 5;
    }

    myOLED.text(78, 37, "\xB3");

    myOLED.text(49, 13, "~");
    myOLED.text(75, 11, "-");

    myOLED.display();
}

void emojiHappy()
{
    int widthLine = 0;
    int heightLine = 0;

    myOLED.erase();

    for (int i = 0; i <= 12; i++)
    {
        myOLED.text(widthLine + 32, 3, "\xC3");
        myOLED.text(widthLine + 32, 47, "\xC3");
        widthLine = widthLine + 5;
    }
    for (int ii = 0; ii <= 6; ii++)
    {
        myOLED.text(29, 8 + heightLine, "\xB2");
        myOLED.text(93, 8 + heightLine, "\xB2");
        heightLine = heightLine + 6;
    }

    myOLED.text(49, 18, "O");
    myOLED.text(75, 18, "O");

    widthLine = 0;

    for (int j = 0; j <= 5; j++)
    {
        myOLED.text(50 + widthLine, 37, "\xC3");
        widthLine = widthLine + 5;
    }

    myOLED.text(49, 13, "-");
    myOLED.text(76, 12, "\xAA");

    myOLED.text(80, 35, "/");

    myOLED.display();
}

void emojiSad()
{
    int widthLine = 0;
    int heightLine = 0;

    myOLED.erase();

    for (int i = 0; i <= 12; i++)
    {
        myOLED.text(widthLine + 32, 3, "\xC3");
        myOLED.text(widthLine + 32, 47, "\xC3");
        widthLine = widthLine + 5;
    }
    for (int ii = 0; ii <= 6; ii++)
    {
        myOLED.text(29, 8 + heightLine, "\xB2");
        myOLED.text(93, 8 + heightLine, "\xB2");
        heightLine = heightLine + 6;
    }

    myOLED.text(49, 18, "O");
    myOLED.text(75, 18, "O");

    widthLine = 0;

    for (int j = 0; j <= 5; j++)
    {
        myOLED.text(50 + widthLine, 37, "\xC3");
        widthLine = widthLine + 5;
    }

    myOLED.text(80, 40, "\\");
    myOLED.text(45, 40, "/");

    myOLED.text(49, 12, "-");
    myOLED.text(75, 12, "-");

    myOLED.display();
}

void emojiShowcase()
{
    if (millis() - startMillisEmoji <= 5000)
    {
        emojiHappy();
    }
    else if (millis() - startMillisEmoji <= 10000)
    {
        emojiMeh();
    }
    else if (millis() - startMillisEmoji <= 15000)
    {
        emojiSad();
    }
    else
    {
        startMillisEmoji = millis();
    }
}
