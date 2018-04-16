#ifndef IR_Sensor_h
#define IR_Sensor_h
using namespace std;



class IR_Sensor
{
  public:
    IR_Sensor();
    void SETUP(SHARP type, int pin); //this function set up a IR sensor, inputs are sensor type and the pin it connected to.
    float distance(); //this function returns the distance in mm

  private:
    SHARP SensorType;
    unsigned int SensorPin;
}

#endif
