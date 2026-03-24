#pragma once

void lcdSetup();
void lcdTopRowPrint();
void lcdWateringStateLoop(int timeWithoutWaterm, int wateringDuration, int wateringTime);
void lcdHappy();
void lcdMeh();
void lcdSad();
void createCharSetup();
void writeCharLoadingAnimation();
void clearScreen();
void MDTesting();
void createCharSetupRainDrop();
void createCharSetupClock();
void createCharSetupBackslash();
void writeCharClock();
void writeCharRainDrop();
void writeCharBackslash();
void backGroundColor(int red, int green, int blue);
