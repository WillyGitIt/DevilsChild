#ifndef IR_Sensor_h
#define IR_Sensor_h
#include "Settings.h"
using namespace std;

#define averageTime  20
//#define e 2.7182818284590

typedef enum {
  Medium_2Y0A21F06,
  Medium_2Y0A21F44,
  Short_2D120XF1Y,
  Short_2D120XF1Z
} 

SHARP;

class IR_Sensor
{
  public:
    IR_Sensor(SHARP type, unsigned int pin);       //contructor assigns IR sensor type and pin
    float distance();                 //this function returns the distance in mm

  private:
    SHARP SensorType;     
    unsigned int Sensorpin;
};

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
