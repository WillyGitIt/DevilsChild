#include "FSM.h"
#include "Arduino.h"
#include "battery.h"
#include "LED.h"
#include "Initial.h"
#include "Spiral.h"
#include "Avoidance.h"
#include "motor.h"
#include "Ultrasonic_Sensor.h"
#include "Settings.h"

unsigned int CornerCount;
unsigned int Wall_Distance_AddOn;   //the add on distance to wall distance, increase when robot completed 1 spiral

void comms_print(String message)      //print message to both usb and bluetooth
{
  Serial.println(message);
  Serial1.println(message); 
}

STATE initialising() {
  if (0){   //battery dection here
    comms_print("<Initialisation Failed: Low Battery>");
    return STOPPED;
  } else {
    comms_print("<Initialising...>");
    motor.SETUP();
    motor.enable_motors();
    homing();
    CornerCount = 0;
    Wall_Distance_AddOn = 0;
    delay(2000);
    comms_print("<Initialisation Finsihed, Entering Spiraling State...>");
    return SPIRALING;
  }
}

STATE spiraling() {
  if (0){   //battery dection here
    comms_print("<Spiraling State Entering Failed: Low Battery>");
    return STOPPED;
  } else {
    comms_print("<Spiraling State Entered>");
    motor.forward();

    //if four corners has been visited (1 spiral done), then reset corner count and reduced spiral size for next loop
    if (CornerCount > 3){                   
      CornerCount = 0;
      Wall_Distance_AddOn += 20;
    }

    //When a wall is detected.... 
    if (wallDetect()){
      comms_print("<Wall Detected, Advancing to Wall...>");
      Ultrasonic_Sensor Ultra;

      //check left and right, if equal-ish, then program is finsihed
      if (abs(Ultra.USmeasure(0) - Ultra.USmeasure(180)) < 10){
        return STOPPED;
      }

      //get closer to the wall
      while(obstacle(3) > (Wall_Distance + Wall_Distance_AddOn)){
        motor.forward();
      }
      motor.stop();
      comms_print("<Wall Reached, Turning...>");
      
      //do a right turn
      motor.cw(90);
      motor.WallAlign();
      CornerCount++;
      return SPIRALING;

      //when obstacle detected...
    } else if (obstacle(0)){
      comms_print("<Obstacle Detected, Advancing to Obstacle...>");
      
      //get closer to the obstacle
      while(obstacle(3) > obstacle_stopDistance){
        motor.forward();
      }
      motor.stop();
      comms_print("<Obstacle Reached, Entering Avoidance State...>");
      return AVOIDANCE;

    //or nothing happends....Charge!!!!!!!
    } else {
      return SPIRALING;
    }
  }
}

STATE avoidance()  {
   if (0){    //battery dection here
    comms_print("<Avoidance State Entering Failed: Low Battery>");
    return STOPPED;
  } else {
    comms_print("<Avoidance State Entered>");

    //'period' is used to record how long we shifted right for, use this to shift back to left later
    //when recording period, shift right is done
    unsigned long period = obstacle_shift_right();
    
    //detecting obstacle while moving forward 
    if(!obstacle_foward()){
      obstacle_shift_left(period);
      comms_print("<Avoidance Performed, Entering Spiraling State...>");
      return SPIRALING;
    } else {
      comms_print("<Avoidance Interupted, Entering Spiraling State...>");
      return SPIRALING;
    }
  }
}

STATE stopped() {
  comms_print("<Program Stopped>");
  is_battery_voltage__not_OK();
  motor.disable_motors();
  slow_flash_LED_builtin();
  return STOPPED;
}




