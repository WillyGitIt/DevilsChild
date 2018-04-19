#ifndef IR_Sensor_h
#define IR_Sensor_h
using namespace std;



class IR_Sensor
{
  public:
    IR_Sensor(SHARP type, int pin);   //contructor assigns IR sensor type and pin 
    float distance();                 //this function returns the distance in mm

  private:
    SHARP SensorType;     
    unsigned int SensorPin;
}

#endif
