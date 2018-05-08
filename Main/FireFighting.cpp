#include "Arduino.h"
#include "FireFighting.h"
#include "Settings.h"



Phototrans phototrans;

void FireDetection()
{
  motor.turnleft(90);
  delay(500);
  for (unsigned int i = 0; i <= 180; i++){
    motor.turnright(1);
    if (phototrans.isFire()){
      FireExtinguish();
      return;
    }
  }
}

void FireExtinguish()
{
  fan.on();
  while(phototrans.isFire()){}
  fan.off();
}

void fanOFF()
{
  digitalWrite(fanPIN,HIGH);
}