#include "Motor.h"
#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include "mpu_gyro.h"
//#include "IR_Sensor.h"

MPU mpu;
//IR_Sensor IR_front_left;
//IR_Sensor IR_front_right;
//IR_Sensor IR_wall_front;
//IR_Sensor IR_wall_back;

int corner = 1;
float angle_reading;

void setup() {
  motor.SETUP();
  motor.enable_motors();
  mpu.mpu_setup();
  Serial.begin(9600); 
  //IR_front_left.setup(Medium_2Y0A21F21, 29)
}

void loop() {
  /*//testing rotation of robot
  motor.forward(0,0);
  delay(1000);
  motor.forward(2,0);
  delay(1000);
  motor.forward(-2,0);
  delay(1300);*/

  /*//testing strafe of robot
  motor.forward(0,0);
  delay(1000);
  motor.forward(0,2);
  delay(3000);
  motor.forward(0,-2);
  delay(3000);*/

  /*//testing robot to go in straight line realigning with mpu feedback
  angle_reading = mpu.get_angle();
  Serial.print("Angle: ");
  Serial.println(angle_reading);
  motor.forward(angle_reading,0);*/

  /*//testing of robot to turn for 90 degrees then go straight again with new angle
  //currently it doesn't align itself, I DON"T KNOW WHYYYYY
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

  //testing of robot to turn for 90 degrees then go straight again with new angle
  if (corner == 1){
    Serial.print("Angle: ");
    Serial.println(angle_reading);
    for (int count = 0; count < 1230; count++) //trial and error showed that 1230 counts gives roughly a 90 degree turn
    {
      angle_reading = mpu.get_angle();
      motor.cw();
    }
    motor.stop();
    delay(500); //the delay is necessary for the MPU to recompose itself
    corner = 0;
    mpu.reset_angle_reading();
   
  } else {
    
    angle_reading = mpu.get_angle();
    Serial.print("Angle: ");
    Serial.println(angle_reading);
    motor.forward(angle_reading,0); 
  }

  //obstacle in distance < 50mm then clockwise
  //mpu.get_angle(&angle_reading);
  //motor.forward(angle_reading,0);

  //if (IR_front_left.distance() < 300) {
    //motor.forward(0,0);
    //delay(1000);
 // }




  

}
