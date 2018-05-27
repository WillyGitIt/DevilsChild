#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

/* creating a motor class */

class mclass{
  public:
    mclass();
    void SETUP();
    void disable_motors(); //good
    void enable_motors(); //good
    void stop(); //good
    void forward(); //good
    void motor_write(int speed_left_front, int speed_left_rear,int speed_right_rear, int speed_right_front); //good
    void reverse(); //good
    void ccw(int degree);
    void cw(int degree);
    void ccw();
    void cw();
    void shift_left();
    void shift_right();
    void wallAlign();
};

extern mclass motor; //Can access class through 'motor' keyword.

#endif
