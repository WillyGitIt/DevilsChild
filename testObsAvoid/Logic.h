#ifndef Logic_h
#define Logic_h

unsigned int wallDirection;

void Sensor_Setup();        //creat sensor objects and assign them to pins
bool wallDetect();          //detect if there is a Wall infront, return true if there is a wall //good
void homing();              //use at the beginning of the program, to go close and parallel to a wall
bool obstacleDetect();//int clearDistance); //detect if there is an obstacle infront within a given distance "clearDistance", returns true if there isan obstacle
void obstacleAvoid();
void shiftRightAvoid(float objDist);
void forwardAvoid();
void shiftLeftAvoid(float wallDist);
void spiral();            //decide the next postition to go and execute and movements 
void mapping();             //to be decided 

#endif
