//current

#include "Motor.h"
//#include <Wire.h>
//#include <FaBo9Axis_MPU9250.h>
//#include "mpu_gyro.h"
//#include "IR_Sensor.h"

//MPU mpu;
//IR_Sensor IR_front_left;
//IR_Sensor IR_front_right;
//IR_Sensor IR_wall_front;
//IR_Sensor IR_wall_back;

int corner = 1;
//float angle_reading;
//float x_vel;
bool turnt = false;
bool isPast = false;

void setup() {
  motor.SETUP();
  motor.enable_motors();
//  mpu.mpu_setup();
  Serial.begin(9600); 
 //IR_front_left.SETUP(0, 29)
}

void loop() {
  /*//testing rotation of robot
  motor.forward(0,0);
  delay(1000);
  motor.forward(7,0);
  delay(1000);
  motor.forward(-7,0);
  delay(1300);

  //testing strafe of robot
  motor.forward(0,0);
  delay(1000);
  motor.forward(0,2);
  delay(3000);
  motor.forward(0,-2);
  delay(3000);*/

  /*//testing robot to go in straight line realigning with mpu angle feedback
  angle_reading = mpu.get_angle();
  Serial.print("Angle: ");
  Serial.println(angle_reading);
  motor.forward(angle_reading,0);*/

  /*//testing of robot to turn for 90 degrees then go straight again with new angle
  if (corner == 1){
    
    mpu.get_angle(&angle_reading);
    motor.cw();
    delay(1400);
    motor.stop();
    corner = 0;
    mpu.reset();
    
  } else {
    
    mpu.get_angle(&angle_reading);
    motor.forward(andgle_reading,0); 
    delay(1000);
  }*/

  /*//testing of robot to turn for 90 degrees then go straight again with new angle //old logic
  if (corner == 1){
    Serial.print("Angle: ");
    Serial.println(angle_reading);
    for (int count = 0; count < 1230; count++) //trial and error showed that 1230 counts gives roughly a 90 degree turn
    {
      angle_reading = mpu.get_angle();
      motor.cw(angle_reading);
    }
    motor.stop();
    delay(500); // the delay is necessary for the MPU to like compose itself. Otherwise the angle readings don't work.
    mpu.reset_angle_reading();
    corner = 0;
   
  } else {
    
    angle_reading = mpu.get_angle();
    Serial.print("Angle: ");
    Serial.println(angle_reading);
    motor.forward(angle_reading,0); 
  }*/

  /*//testing of robot to turn for 90 degrees then go straight again with new angle //new logic
  while (corner == 1){
    Serial.print("Angle: ");
    Serial.println(angle_reading);
    angle_reading = mpu.get_angle();
    turnt = motor.cw(angle_reading, 90);
    if (turnt == true) {
      mpu.reset_angle_reading();
      corner = 0;
    }
  }
  
  angle_reading = mpu.get_angle();
  Serial.print("Angle: ");
  Serial.println(angle_reading);
  motor.forward(angle_reading,0);*/

 /*//trialling turning it for different angles
  
  for (int count = 90; count <= 180; count = count + 90){
      while (turnt == false) {
           //Serial.print("Angle: ");
           //Serial.println(angle_reading);
          angle_reading = mpu.get_angle();
          turnt = motor.cw(angle_reading, count);
      }
      mpu.reset_angle_reading();
      turnt = false;
  }*/

  /*//Testing shiting the robot right and left
  motor.shift_left();
  delay(2000);

  motor.shift_right();
  delay(2000);*/

  /*//testing robot to go in straight line with mpu drift feedback
  x_vel = mpu.get_x_vel();
  Serial.print("X Velocity: ");
  Serial.println(x_vel);
  motor.forward(0,x_vel);*/

/*//---------------DEMONSTRATION-------------------------------

  //angle_reading = mpu.get_angle();
  //motor.forward(angle_reading,0);

  while (turnt == false) {
      angle_reading = mpu.get_angle();
      turnt = motor.cw(angle_reading, 90);
  }
  mpu.reset_angle_reading();
  turnt = false;

  motor.shift_right();
  delay(1200);
  
  while (isPast == false) {
    unsigned long t_now = millis();
    isPast = motor.past_obsta_forward (t_now);
  }

  motor.shift_left();
  delay(1200);

  mpu.reset_angle_reading();
  
  while(1) {
      angle_reading = mpu.get_angle();
      motor.forward(angle_reading,0);
  }
  

//--------------------------------------------------------*/
//mpu is incorporated into motor code.

//testing of robot to go straight
//motor.forward();

//testing of robot to turn for 90 degrees then go straight again with new angle
  while (corner == 1){
    turnt = motor.cw(90);
    if (turnt == true) {
      corner = 0;
    }
  }
  motor.forward();

}







