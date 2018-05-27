//Note: The Vex Motor Controller 29 uses Servo Control signals to determine speed and direction, with 0 degrees meaning
//neutral https://en.wikipedia.org/wiki/Servo_control

/* !!! Make sure that there are no left_font instead of left_front and same for right, in any other code*/

#include "Motor.h"
#include <Arduino.h>
#include "Settings.h"
#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include "mpu_gyro.h"
#include <Servo.h> //Library that allows Arduino board to control the servo motors.
#include "IR_sensor.h"
float angle_reading;
float X_velocity;

// Setting PID values
float kp = 2.2;
//float ki = 1;

// initialising speed variables for each motor.
int speed_left_front;
int speed_left_rear;
int speed_right_rear;
int speed_right_front;

int first_ang_reading = 1;
float angle_reading_desired;

int first_time_reading = 1;
unsigned long t_desired;

float err;
float control_speed;
float p_speed;

Servo left_front_motor;  // create servo object to control Vex Motor Controller 29
Servo left_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_front_motor;  // create servo object to control Vex Motor Controller 29

//string previous_motion = '';
//string current_motion = '';

//Constructor - Create 'mclass' where all the functions relating to the motor are classified under mclass.
mclass::mclass(){
}

//Set up and calibration
void mclass::SETUP()
{
  mpu.mpu_setup();
}

void mclass::disable_motors() // Should be called in the stop state
{
  left_front_motor.detach();  // detach the servo on pin left_front to the servo object
  left_rear_motor.detach();  // detach the servo on pin left_rear to the servo object
  right_rear_motor.detach();  // detach the servo on pin right_rear to the servo object
  right_front_motor.detach();  // detach the servo on pin right_front to the servo object

  pinMode(Motor_LF_Pin, INPUT);
  pinMode(Motor_LR_Pin, INPUT);
  pinMode(Motor_RR_Pin, INPUT);
  pinMode(Motor_RF_Pin, INPUT);
}

void mclass::enable_motors() // Should be called in the initialising state
{
  left_front_motor.attach(Motor_LF_Pin);  // attaches the servo on pin left_front to the servo object
  left_rear_motor.attach(Motor_LR_Pin);  // attaches the servo on pin left_rear to the servo object
  right_rear_motor.attach(Motor_RR_Pin);  // attaches the servo on pin right_rear to the servo object
  right_front_motor.attach(Motor_RF_Pin);  // attaches the servo on pin right_front to the servo object
  return;
}
void mclass::stop() //Stop
{
    speed_left_front = 1500;
    speed_left_rear = 1500;
    speed_right_rear = 1500;
    speed_right_front = 1500;

    motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
    return;
}

void mclass::forward()
{
/*     if (previous_motion != 'forward')
    {
        mpu.reset();
    }
*/
    angle_reading = mpu.get_angle();
    X_velocity = mpu.get_x_vel(); //not sure if x-velocity even works
    
    //checking for angle rotation before drift since drift does not occur often (according to trials)
    if (angle_reading <= -5){
      
      //rotate anticlockwise (minus same amount for each wheel)
      // !! maybe could times the degree by microSeconds to act as a controller almost? do after diagonal done.
      speed_left_front = 1650;
      speed_left_rear = 1650;
      speed_right_rear = 1250;
      speed_right_front = 1250;
      
    } else if (angle_reading >= 5){
      
      //rotate clockwise (ADD same amount for each wheel)
      speed_left_front = 1750;
      speed_left_rear = 1750;
      speed_right_rear = 1350;
      speed_right_front = 1350;
    
    } else if (X_velocity >= 500){
      
      //vehicle is drifting right therefore strafe left - weaker than strafing right therefore the diff between the speed values is greater 
        speed_left_front = 1600; // - speed_val
        speed_left_rear = 1800; // + speed_val
        speed_right_rear = 1400; // + speed_val
        speed_right_front = 1200; // - speed_val
    
    } else if (X_velocity <= -500){
      
        //vehicle is drifting left therefore strafe right
        speed_left_front = 1750; // + speed_val
        speed_left_rear = 1650; // - speed_val
        speed_right_rear = 1250; // - speed_val
        speed_right_front = 1350; // + speed_val
    
    } else {
      
        //equalise the motor speeds.
        speed_left_front = 1700;
        speed_left_rear = 1700;
        speed_right_rear = 1300;
        speed_right_front = 1300;
        
    }
    
    angle_reading = mpu.get_angle();
    motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
    return;

  //  previous_motion = 'forward';
}

void mclass::reverse ()
{
    speed_left_front = 1250;
    speed_left_rear = 1250;
    speed_right_rear = 1750;
    speed_right_front = 1750;

    motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
    return;
}

void mclass::shift_left ()
{
    speed_left_front = 1500 - 200; // minus speed value
    speed_left_rear = 1500 + 200;  // plus speed value
    speed_right_rear = 1500 + 200;  // plus speed value
    speed_right_front = 1500 - 200;  // minus speed value

    motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
    return;
  
}

void mclass::shift_right ()
{

    speed_left_front = 1500 + 200; // plus speed value
    speed_left_rear = 1500 - 200;  // minus speed value
    speed_right_rear = 1500 - 200;  // minus speed value
    speed_right_front = 1500 + 200;  // plus speed value

    motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
    return;

}

//this function will rotate the robot counter clockwise for an inputted amount of degrees.
//this hasn't been tested completely
bool mclass::ccw (int degree)
{
    //pid controller
    angle_reading = mpu.get_angle();
    err = angle_reading - degree;
    
    if (err < 0.5) {
       
       stop();
       delay(500); // the delay is necessary for the MPU to like compose itself. Otherwise the angle readings don't work.
       mpu.reset_angle_reading();
       return true;
       
    } else {

       p_speed = min(err * kp, 200);
       
       //integral = (err * t_diff) + integral;
       //i_speed = integral*ki;
       
       control_speed = p_speed;
        
       speed_left_front = 1400 - (control_speed);
       speed_left_rear = 1400 - (control_speed);
       speed_right_rear = 1400 - (control_speed);
       speed_right_front = 1400 - (control_speed);
       
       angle_reading = mpu.get_angle();
       motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
       
       return false;
    }
}

//this function will rotate the robot clockwise for an inputted amount of degrees.
bool mclass::cw (int degree)
{
    //pid controller
    angle_reading = mpu.get_angle();
    err = angle_reading + degree;
    
    if (err < 0.5) {
       
       stop();
       delay(500); // the delay is necessary for the MPU to like compose itself. Otherwise the angle readings don't work.
       mpu.reset_angle_reading();
       
       return true;
       
    } else {

       p_speed = min(err * kp, 200);
       
       //integral = (err * t_diff) + integral;
       //i_speed = integral*ki;
       
       control_speed = p_speed;
        
       speed_left_front = 1600 + (control_speed);
       speed_left_rear = 1600 + (control_speed);
       speed_right_rear = 1600 + (control_speed);
       speed_right_front = 1600 + (control_speed);

       angle_reading = mpu.get_angle();
       motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
       
       return false;
    }
}

//this function will move the robot forwards until it's past the obstacle
bool mclass::past_obsta_forward (unsigned long t_now)
{
    if (first_time_reading == 1) {    
       t_desired = t_now + 1500;
       first_time_reading = 0;
       
       speed_left_front = 1700;
       speed_left_rear = 1700;
       speed_right_rear = 1300;
       speed_right_front = 1300;
       
       motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
       
       return false;
       
    } else if (t_now >= t_desired) {
       first_time_reading = 1;

       stop();
       delay(500); // the delay is necessary for the MPU to like compose itself. Otherwise the angle readings don't work.
       
       return true;
    }
}

// This writes to the motors the speed of acceleration.
void mclass::motor_write(int speed_left_front, int speed_left_rear,int speed_right_rear, int speed_right_front){

   left_front_motor.writeMicroseconds(speed_left_front);
   left_rear_motor.writeMicroseconds(speed_left_rear);
   right_rear_motor.writeMicroseconds(speed_right_rear);
   right_front_motor.writeMicroseconds(speed_right_front);
   return;

}

void mclass::cw(){
  motor_write(1600,1600,1600,1600);
  return;
}

void mclass::ccw(){
  motor_write(1400,1400,1400,1400);
  return;
}

void mclass::WallAlign(){
  IR_Sensor Front_IR(IR_Type_SF, IR_side_front_PIN);
  IR_Sensor Back_IR(IR_Type_SB, IR_side_back_PIN);
  while (abs(Front_IR.distance() - Back_IR.distance()) > 1){
    if(Front_IR.distance() > Back_IR.distance()){
      ccw();
    }else{
      cw();
    }
  }
  stop();
}


mclass motor = mclass(); // mclass can be accessed via motor keyword as well as mclass.
