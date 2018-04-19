#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

/* creating a motor class */

class mclass{
  public:
    mclass();
    void SETUP();
    int showspeed_val(); //good
    int showspeed_change(); //good
    void writespeed_val(int a); //good
    void writespeed_change(int b); //good
    void disable_motors(); //good
    void enable_motors(); //good
    void stop(); //good
    void forward(float get_angle, float get_X_velocity); //good
    void motor_write(int speed_left_front, int speed_left_rear,int speed_right_rear, int speed_right_front); //good
    void reverse(); //good
//    void ccw();
    void cw();
    void strafe_left ();
};

extern mclass motor; //Can access class through 'motor' keyword.

#endif
