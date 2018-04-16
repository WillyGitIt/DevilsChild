#ifndef Logic_h
#define Logic_h

IR_Sensor IR_FL;
IR_Sensor IR_FR;
IR_Sensor IR_L;
IR_Sensor IR_R;

IR_FL.SETUP(3,IR_forward_left_PIN);
IR_FR.SETUP(4,IR_forward_right_PIN);
IR_L.SETUP(1,IR_left_PIN);
IR_R.SETUP(2,IR_right_PIN);

unsigned int wallDirection;


bool WallDetect();
void Homing();
bool ObstacleDetect(int clearDistance);
void Navigate();
void Mapping();

#endif
