#include "controller.hpp"

void setup()
{ 
  Serial.begin(9600);
  randomSeed(analogRead(0));
}
 
void loop()
{
  controller c;
  while(true)
  {
    yield();
    c.tick();
    //delay(1000);
  }
}
