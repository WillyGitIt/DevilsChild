#ifndef IR_Sensor_h
#define IR_Sensor_h
using namespace std;

typedef enum {
  Medium_2Y0A21F21,
  Medium_2Y0A21F44,
  Short_2D120XF1Y,
  Short_2D120XF1Z
  
//  SHARP_DX, //2D120X - SHORT
//  SHARP_Ya, //2Y0A21 - MEDIUM
//  SHARP_YA //2Y0A02 - LONG
} SHARP;

class IR_Sensor
{
  public:
    void setup(int type, int pin); //
    float distance(); //this function returns the distance in mm

  private:
    SHARP sensorType;
    unsigned int sensorPin;
}

#endif
