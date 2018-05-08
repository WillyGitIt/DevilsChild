/* To control the Rover, copy and paste the code below into the Arduino
 software. Ensure the motors are connected to the correct pins. The
 code does not factor in encoders at this time*/

#include "IR_Sensor.h"
#include "Arduino.h"


IR_Sensor::IR_Sensor(SHARP type, unsigned int pin){
    SensorType = type;     
    Sensorpin = pin;
}

float IR_Sensor::distance()
{
  float dis_mm;  //distance in mm
  float addup_readings = 0;

  for(unsigned int i = 0; i < averageTime; i++){
    switch(SensorType){
      //case Short_2D120XF1Y: dis_mm = -19.85 * log(analogRead(Sensorpin)) + 107.97;    
      //case Short_2D120XF1Z: dis_mm =  -17.82 * log(analogRead(Sensorpin)) + 91.97;
//      case Medium_2Y0A21F06: 
//      if (analogRead(Sensorpin) < 180) {
//        dis_mm = -40.66 * log(analogRead(Sensorpin)) + 223.34;
//      } else {  
//        dis_mm = -0.0925 * analogRead(Sensorpin) + 28.058;
//      }

      case Medium_2Y0A21F44: 
        if (analogRead(Sensorpin) < 170) {
          dis_mm = -36.681 * log(analogRead(Sensorpin)) + 198.64;
        } else {  
          dis_mm = -0.0914 * analogRead(Sensorpin) + 26.365;
        }
          
    }
    //addup_readings += dis_mm;
    //delay(5);
  }
  return dis_mm;
  //return addup_readings / averageTime;


}


