#include "Arduino.h"
#include "FireFighting.h"
#include "Settings.h"



Phototrans phototrans;

void FireDetection()
{
<<<<<<< HEAD
  for (unsigned int i = 0; i <= 360; i++){
    motor.turnright(3);
    if (phototrans()){
=======
  motor.turnleft(90);
  delay(500);
  for (unsigned int i = 0; i <= 180; i++){
    motor.turnright(1);
    if (phototrans.isFire()){
>>>>>>> photoTransistors
      FireExtinguish();
      FireDetection();
      return;
    }
  }
}

void FireExtinguish()
{
<<<<<<< HEAD
  fanON();
  while(phototrans()){}
  delay(fanDELAY);
  fanOFF();
}

void fanON()
{
  pinMode(fanPIN, OUTPUT);
  digitalWrite(fanPIN,LOW);
=======
  fan.on();
  while(phototrans.isFire()){}
  fan.off();
>>>>>>> photoTransistors
}

void fanOFF()
{
  digitalWrite(fanPIN,HIGH);
}