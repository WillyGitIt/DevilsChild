#include "Arduino.h"
#include "Motor.h"
#include "Settings.h"
#include "Ultrasonic_Sensor.h"
#include "IR_Sensor.h"
#include "phototrans.h"
#include <hcsr04.h>

Phototrans Phototrans(0.2, 14, 5, 15, 4);

bool testingYes = true;
int turnDist = 8;

int wallSetDist = 20;
int corner = 0;
int wallCount = 0;
int obsCount = 0;

//------Setup for IR------//
IR_Sensor IR_FL(IR_Type_FL,IR_FL_PIN);
IR_Sensor IR_FR(IR_Type_FR,IR_FR_PIN);
IR_Sensor IR_SF(IR_Type_SF,IR_SF_PIN);
IR_Sensor IR_SB(IR_Type_SB,IR_SB_PIN);

//------Setup for US------//
Ultrasonic_Sensor ultrasonic(SERVO_PIN, TRIG_PIN, ECHO_PIN, US_MinRange, US_MaxRange);

bool wallDetect()   //checks if there is a wall infront of the robot, true if there is wall, false if no wall.
{
  int mid_dis = ultrasonic.USmeasure(90);
  float left_dis = IR_FL.distance();
  float right_dis = IR_FR.distance();
  
  float reference_mid = (left_dis + right_dis) * 0.5;
  if ((mid_dis > (reference_mid - 4)) && (mid_dis < (reference_mid + 4))){
    return true;
  }else{
    return false;
  }
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

bool obstacleDetect() {
  
  float FLdist = IR_FL.distance();
  float FRdist = IR_FR.distance();
  float USdist = ultrasonic.USmeasure(90);
  
  if ( (min(FLdist,USdist) <  30) && (FRdist > 30)) {
    return true;
  } else if ((min(FRdist,USdist) < 30) && (FLdist > 30)) {
    return true;
  } else {
    return false;
  }
  
 /* unsigned int clearAngle;
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

void shiftRightAvoid(float objDist) {
  
  bool hasSeenObs = false;
  bool completed = false;
  
  while(!completed){
      if (IR_FL.distance() <= objDist) { // doesn't matter which IR sensor detected the obstacle, if the the left IR sensor detects the obj infront, then note it down.
        hasSeenObs = true;
        motor.shift_right();
      } else if ((hasSeenObs) && (IR_FL.distance() >= 20)){ // object has been infront of left IR and now the left IR doesn't detect any objects infront of it, therefore it has past obstacle.
        completed = true;    
      } else { // otherwise keep moving right
      motor.shift_right();
      }
  } 
  return;
}
  
void forwardAvoid()//moving past the obstacle in the forwards motion
{
  bool frontSeenObstacle = false;
  bool backSeenObstacle = false;
  bool fireChecked = false;
  bool completed = false;

  while (!fireChecked){
    if (IR_SF.distance() <= 10) {
      frontSeenObstacle = true;
      motor.forward();
    } else if (frontSeenObstacle && (IR_SF.distance() >= 20)){
      motor.stop();
      delay(2000);
      if (Phototrans.isFire()) {
        digitalWrite(34, LOW);   
      } else {
        digitalWrite(34, HIGH);
        fireChecked = true;
      }
    } else {
      motor.forward();
    }
  }

  while (!completed){
     if (IR_SB.distance() <= 10) { // if side back IR detects an object infront of it, then it'll note it down in count.
        backSeenObstacle = true;
        motor.forward();
     } else if (backSeenObstacle && (IR_SB.distance() >= 20)) { //object has been infront of side back IR and now the object isn't detected, therefore object has been past.
        completed = true;//exit while loop
     } else { //otherwise just keep moving forward.
        motor.forward();
     }
  }
  return;
}

void shiftLeftAvoid(float wallDist)
{
  bool completed = false;
  
  while(!completed)
  { 
    if (((IR_SF.distance() + IR_SB.distance())*0.5) <= wallDist) { // original line of motion is detected
      completed = true;//therefore exit loop.
    } else { //otherwise keep moving left.
      motor.shift_left();
    }
  }
  return;
}

void obstacleAvoid() { //function only entered if obstacleDetected returns true.

  float objDist = min(min(IR_FR.distance(), IR_FL.distance()),ultrasonic.USmeasure(90)); // eventually add ultrasonic distance
  float wallDist = (IR_SF.distance() + IR_SB.distance())*0.5; //average
  shiftRightAvoid(objDist);
  forwardAvoid();
  if (min(IR_SF.distance(), IR_SB.distance()) < 24){ //not enough room infront
    return;
  } else {  
  shiftLeftAvoid(wallDist);
  motor.wallAlign();
    return;
  }
  
}
    
void spiral()
{
  
    Serial.print(ultrasonic.USmeasure(90));
    Serial.print(",");
    Serial.print(IR_SF.distance());
    Serial.print(",");
    Serial.print(IR_SB.distance());
    Serial.print(",");
    Serial.println(corner);
    //Serial.println("---------------------");
   /*ultrasonic.USmeasure(0);
   delay(6000);*/
    /*if (wallDetect() == true) {
      wallCount = wallCount + 1;
    }
     if (obstacleDetect() == true) {
      obsCount = obsCount + 1;
    }

    Serial.println(wallCount);
    Serial.println(obsCount);
    Serial.println("===================");*/
    if (wallDetect() == true) {
        if (corner == 4){
          wallSetDist = wallSetDist + 20;
          corner = 0;
        }
        while (ultrasonic.USmeasure(90) > wallSetDist){ //keep going forward until at decided distance away from wall
          motor.forward();
        } // robot at distance away from wall.
        motor.reverse();
        delay(25);
        motor.cw(80);
        corner = corner + 1;
        motor.wallAlign();
    } else if (obstacleDetect() == true) {
      obstacleAvoid();
      //STATE == "AVOIDANCE"
    } else {
      motor.forward();
    }
    return;
}
    
    /*motor.stop();
    //delay(500);
    motor.cw(90);
    turnCount = turnCount + 1;
    if (turnCount == 4)
    {
      turnDist = turnDist + 20;
      turnCount = 0;
    }
    return;*/

void mapping()
{
}
    


