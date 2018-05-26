#include "Arduino.h"
#include "Motor.h"
#include "Settings.h"
//#include "Ultrasonic_Sensor.h"
#include "IR_Sensor.h"

bool testingYes = true;

//------Setup for IR------//
IR_Sensor IR_FL(Short_2D120XF1Y,8);
IR_Sensor IR_FR(Short_2D120XF1Z,9);
IR_Sensor IR_SF(Medium_2Y0A21F06,10);
IR_Sensor IR_SB(Medium_2Y0A21F44,11);

//------Setup for US------//
//Ultrasonic_Sensor MyEyes(SPINNYTHING_PIN, TRIG_PIN, ECHO_PIN, US_MinRange, US_MaxRange);

bool wallDetect()   //checks if there is a wall infront of the robot, true if there is wall, false if no wall.
{
  float avgFrontDis = (IR_FL.distance() + IR_FR.distance())*0.5; //gets average from both front IR sensors
  
  if (avgFrontDis <= 5){ //if average front distance is less than 5cm then there is a wall infront
    return true;
  }

  return false;
  
  /*// Follwing code was done by Will.
  int mid_dis = MyEyes.USmeasure(90);
  float left_dis = IR_FL.distance();
  float right_dis = IR_FR.distance();
  float reference_mid = (left_dis + right_dis) / 2;
  if ((mid_dis > (reference_mid - 1.5)) && (mid_dis < (reference_mid + 1.5))){
    return true;
  }else{
    return false;
  }*/
}

void homing() //not using this function yet.
{
  /*//keep safe distance to the wall
  if(wallDetect()){
    while ((float IR_FL.distance() > 150) && (float IR_FR.distance() > 150)){
      motor.forward();
    }
    while(float IR_FL.distance() > float IR_FR.distance()){
      motor.turnright();
    }
    while(float IR_FL.distance() < float IR_FR.distance()){
      motor.turnleft();
    }
    motor.turnright(90);
  }else{
    motor.turnleft(30);
    homing();
  }*/
}

bool obstacleDetect() {//int clearDistance)
  if (IR_FR.distance() <= 20 || IR_FL.distance() <= 20) {
    return true;
  } else {
    return false;
  }
  
  /*unsigned int clearanceCount = 0;
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
  return false;*/
}

void obstacleAvoid() { //function only entered if obstacleDetected returns true.

  //used in logic for deciding how far through the avoidance we are.
  //reset at the start of each obstacle avoidance.
  bool hasPastSidewaysR = false;
  bool hasPastForwards = false;
  bool hasShiftedBack = false;
  
  float objDist = min(IR_FR.distance(), IR_FL.distance()); // eventually add ultrasonic distance
  float wallDist = min(IR_SF.distance(), IR_SB.distance());
  int count = 0; //used for logic in moving around obstacle.
  
  //moving to the right, sideways of obstacle
  while (hasPastSidewaysR == false) { 
     
      if (IR_FL.distance() <= objDist) { // doesn't matter which IR sensor detected the obstacle, if the the left IR sensor detects the obj infront, then note it down in count.
        count = 1;
        motor.shift_right();
      } else if (count == 1 && IR_FL.distance() >= 20){ // object has been infront of left IR and now the left IR doesn't detect any objects infront of it, therefore it has past obstacle.
        count = 0; //reset count for use in the next while loop.
        hasPastSidewaysR = true; //exit loop.
      } else { // otherwise keep moving right
      motor.shift_right();
      }
      
  }
  
  //moving past the obstacle in the forwards motion
  while (hasPastForwards == false) {
    
     if (IR_SB.distance() <= 10) { // if side back IR detects an object infront of it, then it'll note it down in count.
      count = 1;
      motor.forward();
     }
     else if ((count == 1) && (IR_SB.distance() >= 20)) { //object has been infront of side back IR and now the object isn't detected, therefore object has been past.
        hasPastForwards = true; //exit while loop
     } else { //otherwise just keep moving forward.
        motor.forward();
     }
     
  }

  //moving back to the original line of motion.
  while (hasShiftedBack == false) {
    
    if (min(IR_SF.distance(), IR_SB.distance()) <= wallDist) { // original line of motion is detected
      hasShiftedBack = true; //therefore exit loop.
    } else { //otherwise keep moving left.
      motor.shift_left();
    }
    
  }
  
  return;
}

void navigate()
{
  /*if(obstacleDetect()){
    motor.right(50);
  }else{
    motor.forward(800);
  }*/
}

void mapping()
{

}


