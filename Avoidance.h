#ifndef Avoidance_h
#define Avoidance_h
#include <Arduino.h>

bool obstacle(int sensor);    //Returns boolean, true if there is an obstacle infront of a sensor. Input: 0 is to detect from all 3 front facing sensors
                              //1 is to detect from left IR, 2 is rear IR, 3 is from Ultrasonic at 90 degree(forawrd)

unsigned long obstacle_shift_right();       //shift right till pass obstacle and return a time for shifting length

void obstacle_shift_left(unsigned long period);   //shift back left the same for 'period' milliseconds

bool obstacle_foward();             //go forward and pass the obstacle, but stop when another obstacle (or wall) detected
                                    //this function also includes fire fighting
#endif

