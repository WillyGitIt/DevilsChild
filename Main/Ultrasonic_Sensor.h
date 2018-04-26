#ifndef Ultrasonic_Sensor_h
#define Ultrasonic_Sensor_h
using namespace std;

class Ultrasonic_Sensor
{
  public:
    Ultrasonic_Sensor(int ServoPin, int TrigPin, int EchoPin, int MinRange, int MaxRange);  //constructor
    void UltraSonicScan();                  //scan front 180 degree and write data to 'FrontScan'                                        
    int USmeasure(unsigned int degree);     //measure the distance with US sensor in a certain direction "degree"
    float getFrontScan();                   //return FrontScan
    
  private:
    float FrontScan[180];                   //record distances of front 0-180 degrees, from left to right
}

#endif