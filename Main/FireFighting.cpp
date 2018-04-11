#include "Arduino.h"
#include "FireFighting.h"

void FireDetection()
{
  motor.turnleft(90);
  delay(500);
  for (unsigned int i = 0; i <= 180; i++){
    motor.turnright(1);
    if (phototrans()){
      FireExtinguish();
      return;
    }
  }
}

void FireExtinguish()
{
  fan.on();
  while(phototrans()){}
  fan.off();
}

