#ifndef Logic_h
#define Logic_h

unsigned int wallDirection;

void Sensor_Setup();        //creat sensor objects and assign them to pins
bool WallDetect();          //detect if there is a Wall infront, return true if there is a wall
void Homing();              //use at the beginning of the program, to go close and parallel to a wall
bool ObstacleDetect(int clearDistance); //detect if there is an obstacle infront within a given distance "clearDistance", returns true if there is an obstacle
void Navigate();            //decide the next postition to go  and execute and movements 
void Mapping();             //to be decided 

#endif
