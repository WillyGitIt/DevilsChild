#ifndef Ultrasonic_Sensor_h
#define Ultrasonic_Sensor_h
using namespace std;

float FrontScan[180]; 
void US_setup();
void UltraSonicScan();
int USmeasure(unsigned int degree);

#endif
