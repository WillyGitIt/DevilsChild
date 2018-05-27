#include "Motor.h"
#include "Spiral.h"
#include "Settings.h"
#include "Ultrasonic_Sensor.h"
#include "IR_Sensor.h"
#include <Arduino.h>

bool wallDetect()   //checks if there is a wall infront of the robot, true if there is wall, false if no wall.
{
  Ultrasonic_Sensor ultrasonic;
  IR_Sensor IR_FL(IR_Type_FL,IR_forward_left_PIN);
  IR_Sensor IR_FR(IR_Type_FR,IR_forward_right_PIN);
  
  int mid_dis = ultrasonic.USmeasure(90);
  float left_dis = IR_FL.distance();
  float right_dis = IR_FR.distance();
  
  float reference_mid = (left_dis + right_dis) * 0.5;
  if (abs(mid_dis - reference_mid) < 4){
    return true;
  }else{
    return false;
  }
}
