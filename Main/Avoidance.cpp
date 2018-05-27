#include "Motor.h"
#include "Avoidance.h"
#include <Arduino.h>
#include "IR_Sensor.h"
#include "Settings.h"
#include "Ultrasonic_Sensor.h"
#include "phototrans.h"
#include "Settings.h"

//setting up a phototransistor object
Phototrans Phototrans(alphaIn, front5photo, front3photo, back5photo, back3photo);


bool obstacle(int sensor){
  unsigned int distance;
  if (sensor == 0){
    Ultrasonic_Sensor US;
    IR_Sensor IRL(IR_Type_FL, IR_forward_left_PIN);
    IR_Sensor IRR(IR_Type_FR, IR_forward_right_PIN);
    distance = min(IRL.distance(),IRR.distance());
    distance = min(US.USmeasure(90),distance);

    if (distance < obstacle_dectectDistance){
      return true;
    } else {
      return false;
    }
  } else if (sensor == 1){
    IR_Sensor IRL(IR_Type_FL, IR_forward_left_PIN);
    distance = IRL.distance();

    if (distance < obstacle_dectectDistance){
      return true;
    } else {
      return false;
    }
  } else if (sensor == 2){
    IR_Sensor IRB(IR_Type_SB, IR_side_back_PIN);
    distance = IRB.distance();
    
    if (distance < 5){
      return true;
    } else {
      return false;
    }
  } else {
    Ultrasonic_Sensor US;
    distance = US.USmeasure(90);
    
    if (distance < obstacle_dectectDistance){
      return true;
    } else {
      return false;
    }
  }
}

unsigned long obstacle_shift_right(){
  bool previous = false;
  bool current = false;
  unsigned long travelled_time = millis();
  while(!(previous && (current = !obstacle(1)))){
    motor.shift_right();
    previous = current;
  }
  
  delay(300);
  motor.stop();
  travelled_time = millis() - travelled_time;  
  return travelled_time;
}

void obstacle_shift_left(unsigned long period){
  motor.shift_right();
  delay(period);
  motor.stop();
}

bool obstacle_foward(){
  bool previous = false;
  bool current = false;
  while(!(previous && (current = !obstacle(2)))){
    if (!obstacle(0)){      //if 
      motor.forward();
      previous = current;
    } else if (Phototrans.isFire()) {     //detecting fire
      //fan on
      digitalWrite(fanPIN, LOW);
      if (!Phototrans.isFire()) {
        digitalWrite(fanPIN, HIGH);  //fan off
      }
      motor.stop();
    } else {            //a wall too close
      motor.stop();
      return false;
    }
  }
  delay(500);
  motor.stop();
  return true;
}

