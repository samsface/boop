#include "controller.hpp"

void setup()
{ 
  randomSeed(analogRead(0));
}
 
void loop()
{
  controller c;
  
  while(true)
  {
    c.tick();
    yield();
  }
}
