#include "Arduino.h"
#include "FireFighting.h"
#include "Settings.h"



void FireDetection()
{
  for (unsigned int i = 0; i <= 360; i++){
    motor.turnright(3);
    if (phototrans()){
      FireExtinguish();
      FireDetection();
      return;
    }
  }
}

void FireExtinguish()
{
  fanON();
  while(phototrans()){}
  delay(fanDELAY);
  fanOFF();
}

void fanON()
{
  pinMode(fanPIN, OUTPUT);
  digitalWrite(fanPIN,LOW);
}

void fanOFF()
{
  digitalWrite(fanPIN,HIGH);
}