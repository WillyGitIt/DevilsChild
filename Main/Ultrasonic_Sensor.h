#ifndef Ultrasonic_Sensor_h
#define Ultrasonic_Sensor_h
using namespace std;

class Ultrasonic_Sensor
{
  public:
    Ultrasonic_Sensor();  //constructor
    void UltraSonicScan();                  //scan front 180 degree and write data to 'FrontScan'                                        
    int USmeasure(unsigned int degree);     //measure the distance with US sensor in a certain direction "degree"
    float getFrontScan();                   //return FrontScan
    
  private:
    unsigned int Servo_Pin;
    unsigned int Trig_Pin;
    unsigned int Echo_Pin;
    unsigned int Min_Range;
    unsigned int Max_Range;
    float FrontScan[180];                   //record distances of front 0-180 degrees, from left to right
};

#endif
