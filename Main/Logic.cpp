#include "Arduino.h"
#include "Motor.h"

void Homing()
{
  //keep safe distance to the wall
  while ((IR_rear < 200) || (IR_front < 200))
    motor.right();
  }
  
  //rotate parallel to the wall
  while (IR_front != IR_rear)
  {
    if (IR_front > IR_rear)
    {
      motor.turnleft();
    } else if (IR_front < IR_rear)
    {
      motor.turnright();
    }
  }

  while ((IR_rear < 210) && (IR_front < 210))
  {
    motor.left();
  }

}


bool ObstacleDetect()
{
  unsigned int clearanceCount = 0;
  unsigned int clearAngle;
  const unsigned int clearDistance = 1000;
  float safeDistance;
  float pi = 3.1415926;
  
  for (unsigned int i = 0; i <= 180; i++){

     float radian = i / 180 *pi;
     if ( (radian > atan(clearDistance/130)) && (radian <  (pi - atan(clearDistance/130)))){
      safeDistance = 130 / cos(radian);
     }else{
      safeDistance = clearDistance;
     }
     
     if (FrontScan[i] < safeDistance){
      clearanceCount++;
     }else{
      clearanceCount = 0;
     }

    if (clearanceCount > 2){
      return true;
    }
  }
  return false;
}

void Navigate()
{
  if(ObstacleDetect()){
    motor.right(50);
  }else{
    motor.forward(800);
  }
}
void Mapping();

void move_it()
{
  if ((IR_L > 200) && (IR_R > 200))
  {
    motor.forward();
  } else if (IR_L > 200)
  {
    motor.left();
  } else if (IR_R > 200)
  {
    motor.right();
  } else 
  {
    motor.rightDegree(90);
  }
}

