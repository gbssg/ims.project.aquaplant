#include <Arduino.h>
// put function declarations here:
int myFunction(int, int);

void textOutput()
{
  Serial.println("Function");
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("Hello World");
  textOutput();
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}