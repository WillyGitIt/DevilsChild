//Note: The Vex Motor Controller 29 uses Servo Control signals to determine speed and direction, with 0 degrees meaning
//neutral https://en.wikipedia.org/wiki/Servo_control

/* !!! Make sure that there are no left_font instead of left_front and same for right, in any other code*/

#include "Motor.h"
#include <Arduino.h>
#include <Servo.h> //Library that allows Arduino board to control the servo motors.

int speed_val = 100; // speed_val is the speed value of the wheels. Try not to go over maybe like 300.
int speed_change;

// Setting PID values
float kp = 0.4;
float ki = 0;
float kd = 0;

//Default motor control pins
const byte left_front = 46;
const byte left_rear = 47;
const byte right_rear = 50;
const byte right_front = 51;

// initialising speed variables for each motor.
int speed_left_front;
int speed_left_rear;
int speed_right_rear;
int speed_right_front;

int first_ang_reading = 1;
float angle_reading_desired;

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
// i think that setup is basically what the enable function does.

// Need to do calibration maybe
}

int mclass::showspeed_val()
{
  return speed_val;
}

int mclass::showspeed_change()
{
  return speed_change;  
}

void mclass::writespeed_val(int a)
{
  speed_val = a;  
}

void mclass::writespeed_change(int b)
{
  speed_change = b;  
}

void mclass::disable_motors() // Should be called in the stop state
{
  left_front_motor.detach();  // detach the servo on pin left_front to the servo object
  left_rear_motor.detach();  // detach the servo on pin left_rear to the servo object
  right_rear_motor.detach();  // detach the servo on pin right_rear to the servo object
  right_front_motor.detach();  // detach the servo on pin right_front to the servo object

  pinMode(left_front, INPUT);
  pinMode(left_rear, INPUT);
  pinMode(right_rear, INPUT);
  pinMode(right_front, INPUT);
}

void mclass::enable_motors() // Should be called in the initialising state
{
  left_front_motor.attach(left_front);  // attaches the servo on pin left_front to the servo object
  left_rear_motor.attach(left_rear);  // attaches the servo on pin left_rear to the servo object
  right_rear_motor.attach(right_rear);  // attaches the servo on pin right_rear to the servo object
  right_front_motor.attach(right_front);  // attaches the servo on pin right_front to the servo object
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

void mclass::forward(float get_angle, float get_X_velocity)
{
    //speed_left_front = 1700;
    //speed_left_rear = 1700;
    //speed_right_rear = 1300;
    //speed_right_front = 1300;

/*     if (previous_motion != 'forward')
    {
        mpu.reset();
    }
*/
    //checking for angle rotation before drift since drift does not occur often (according to trials)
    if (get_angle <= -5){
      
      //rotate anticlockwise (minus same amount for each wheel)
      // !! maybe could times the degree by microSeconds to act as a controller almost? do after diagonal done.
      speed_left_front = 1650;
      speed_left_rear = 1650;
      speed_right_rear = 1250;
      speed_right_front = 1250;
      
    } else if (get_angle >= 5){
      
      //rotate clockwise (ADD same amount for each wheel)
      speed_left_front = 1750;
      speed_left_rear = 1750;
      speed_right_rear = 1350;
      speed_right_front = 1350;
    
    } else if (get_X_velocity >= 1){
      
      //vehicle is drifting right therefore strafe left - weaker than strafing right therefore the diff between the speed values is greater 
        speed_left_front = 1600; // - speed_val
        speed_left_rear = 1800; // + speed_val
        speed_right_rear = 1400; // + speed_val
        speed_right_front = 1200; // - speed_val
    
    } else if (get_X_velocity <= -1){
      
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

/*
// this function will rotate the robot countclockwise for an inputted amount of degrees.
void mclass::ccw_by (int degree)
{
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}
*/
//this function will rotate the robot clockwise for an inputted amount of degrees.
// This should work but need to check - later can just copy for anticlockwise
bool mclass::cw (float angle_reading, int degree)
{
    //rotate clockwise (add same amount for each wheel)
    if (first_ang_reading == 1) {    
       angle_reading_desired = angle_reading - degree;
       first_ang_reading = 0;
       
       speed_left_front = 1650;
       speed_left_rear = 1650;
       speed_right_rear = 1650;
       speed_right_front = 1650;
       
       motor_write(speed_left_front,speed_left_rear,speed_right_rear,speed_right_front);
       
       return false;
       
    } else if (angle_reading <= angle_reading_desired) {
       first_ang_reading = 1;

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

<<<<<<< HEAD:Main/Motor.cpp
mclass motor = mclass();


        Serial1.println("Strafe Right");
        break;
      case 'a'://Turn Right
      case 'A':
        ccw();
        Serial1.println("ccw");
        break;
      case 'd'://Turn Right
      case 'D':
        cw();
        Serial1.println("cw");
        break;
      case '-'://Turn Right
      case '_':
        speed_change = -100;
        Serial1.println("-100");
        break;
      case '=':
      case '+':
        speed_change = 100;
        Serial1.println("+");
        break;
      default:
        stop();
        Serial1.println("stop");
        break;
    }
  }
}

void mclass::disable_motors()
{
  left_font_motor.detach();  // detach the servo on pin left_front to the servo object
  left_rear_motor.detach();  // detach the servo on pin left_rear to the servo object
  right_rear_motor.detach();  // detach the servo on pin right_rear to the servo object
  right_font_motor.detach();  // detach the servo on pin right_front to the servo object

  pinMode(left_front, INPUT);
  pinMode(left_rear, INPUT);
  pinMode(right_rear, INPUT);
  pinMode(right_front, INPUT);
}

void mclass::enable_motors()
{
  left_font_motor.attach(left_front);  // attaches the servo on pin left_front to the servo object
  left_rear_motor.attach(left_rear);  // attaches the servo on pin left_rear to the servo object
  right_rear_motor.attach(right_rear);  // attaches the servo on pin right_rear to the servo object
  right_font_motor.attach(right_front);  // attaches the servo on pin right_front to the servo object
}
void mclass::stop() //Stop
{
  left_font_motor.writeMicroseconds(1500);
  left_rear_motor.writeMicroseconds(1500);
  right_rear_motor.writeMicroseconds(1500);
  right_font_motor.writeMicroseconds(1500);
}

void mclass::forward()
{
  left_font_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_font_motor.writeMicroseconds(1500 - speed_val);
}

void mclass::reverse ()
{
  left_font_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_font_motor.writeMicroseconds(1500 + speed_val);
}

void mclass::ccw ()
{
  left_font_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_font_motor.writeMicroseconds(1500 - speed_val);
}

void mclass::cw ()
{
  left_font_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_font_motor.writeMicroseconds(1500 + speed_val);
}

void mclass::strafe_left ()
{
  left_font_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_font_motor.writeMicroseconds(1500 - speed_val);
}

void mclass::strafe_right ()
{
  left_font_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_font_motor.writeMicroseconds(1500 + speed_val);
}

mclass motor = mclass();

=======
mclass motor = mclass(); // mclass can be accessed via motor keyword as well as mclass.
>>>>>>> motor_nancy:Motor.cpp
