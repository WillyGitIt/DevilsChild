#include "Arduino.h"
#include "Motor.h"
#include "Settings.h"
#include "Ultrasonic_Sensor.h"
#include "IR_Sensor.h"

void Sensors_Setup()
{
  //------Setup for IR------//
  IR_Sensor IR_FL(IR_Type_FL,IR_forward_left_PIN);
  IR_Sensor IR_FR(IR_Type_FR,IR_forward_right_PIN);
  IR_Sensor IR_L(IR_Type_L,IR_left_PIN);
  IR_Sensor IR_R(IR_Type_R,IR_right_PIN);

  //------Setup for US------//
  Ultrasonic_Sensor MyEyes(SPINNYTHING_PIN, TRIG_PIN, ECHO_PIN, US_MinRange, US_MaxRange);
}

bool WallDetect()   // a fuction to check if there is a wall infront
{
  int mid_dis = MyEyes.USmeasure(90);
  float left_dis = IR_FL.distance();
  float right_dis = IR_FR.distance();
  float reference_mid = (left_dis + right_dis) / 2;
  if ((mid_dis > (reference_mid - 1.5)) && (mid_dis < (reference_mid + 1.5))){
    return true;
  }else{
    return false;
  }
}

void Homing()
{
  //keep safe distance to the wall
  if(WallDetect()){
    while ((IR_FL.distance() > 150) && (IR_FR.distance() > 150)){
      motor.forward();
    }
    while(IR_FL.distance() > IR_FR.distance()){
      motor.turnright();
    }
    while(IR_FL.distance() < IR_FR.distance()){
      motor.turnleft();
    }
    motor.turnright(90);
  }else{
    motor.turnleft(30);
    Homing();
  }
}


bool ObstacleDetect(int clearDistance)
{
  unsigned int clearanceCount = 0;
  unsigned int clearAngle;
  float safeDistance;
  float pi = 3.1415926;
  float ScanData =  MyEyes.getFrontScan();

  for (unsigned int i = 0; i <= 180; i++){

     float radian = i / 180 *pi;
     if ( (radian > atan(clearDistance/130)) && (radian <  (pi - atan(clearDistance/130)))){
      safeDistance = 130 / cos(radian);
     }else{
      safeDistance = clearDistance;
     }
     
     if (ScanData[i] < safeDistance){
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

void Mapping()
{

}


