#include "Motor.h"
#include "Arduino.h"
#include <Servo.h>

const byte left_front = 46;
const byte left_rear = 47;
const byte right_rear = 48;
const byte right_front = 49;

int speed_val = 100;
int speed_change;

Servo left_font_motor;  // create servo object to control a servo
Servo left_rear_motor;  // create servo object to control a servo
Servo right_rear_motor;  // create servo object to control a servo
Servo right_font_motor;  // create servo object to control a servo


mclass::mclass(){
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

void mclass::SETUP()
{

}

void mclass::read_serial_command()
{
  if (Serial1.available()) {
    char val = Serial1.read();
    Serial1.print("Speed:");
    Serial1.print(speed_val);
    Serial1.print(" ms ");

    //Perform an action depending on the command
    switch (val) {
      case 'w'://Move Forward
      case 'W':
        forward ();
        Serial1.println("Forward");
        break;
      case 's'://Move Backwards
      case 'S':
        reverse ();
        Serial1.println("Backwards");
        break;
      case 'q'://Turn Left
      case 'Q':
        strafe_left();
        Serial1.println("Strafe Left");
        break;
      case 'e'://Turn Right
      case 'E':
        strafe_right();
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

