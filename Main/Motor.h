#ifndef Motor_h
#define Motor_h

class mclass{
  public:
    mclass();
    void SETUP();
    void read_serial_command();
    void disable_motors();
    void enable_motors();
    void stop();
    void forward();
    void reverse();
    void ccw();
    void cw();
    void strafe_left();
    void strafe_right();
    int showspeed_val();
    int showspeed_change();
    void writespeed_val(int a);
    void writespeed_change(int b);
};

extern mclass motor;

#endif
