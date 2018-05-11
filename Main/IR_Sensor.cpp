/*  distance() returns a distance measurement in centimetres. 
    For the short range, 
*/

#include "IR_Sensor.h"
#include "Arduino.h"


IR_Sensor::IR_Sensor(SHARP type, unsigned int pin){
    SensorType = type;     
    Sensorpin = pin;
}

float IR_Sensor::distance()
{
  float temp;
  for (unsigned int i = 0; i < 50; i++){
    temp += analogRead(Sensorpin);
    delay(1);
  }
  temp = temp / 50;
  
  float dis_mm;  //distance in mm
    switch(SensorType){
        case Short_2D120XF1Y: {
          dis_mm = temp;
            //Serial.println("case 1");
          if (temp < 146) {
            dis_mm = -27.15 * log(temp) + 139.09;
          }
          else if (temp < 212){
            dis_mm = -0.0758 * temp + 16.06;
          }
        } break;    
          
        case Short_2D120XF1Z: {
            //Serial.println("case 2");
           if (temp < 91 ) {
            dis_mm =  -20.67 * log(temp) + 103.22;
           } else if (temp < 176) {
            dis_mm = -0.117 * (temp) + 20.403;            
           } else {
            dis_mm = 0;
           }
        } break;
          
        case Medium_2Y0A21F06:  {
          //dis_mm = temp;     
          if (temp < 176)  {
            dis_mm = -44.68 * log(temp) + 243.38;
          } else if (temp < 311) {  
            dis_mm = -0.109 * temp + 33.277;
          } else {
            dis_mm = 0;
          }      
        
          //Serial.print("case 3 ");    //for debugging
          } break;
          
        case Medium_2Y0A21F44: {
          //dis_mm = temp;
          if (temp < 171) {
            dis_mm = -39.57 * log(temp) + 209.02;
          } else if (temp < 290) {  
            dis_mm = -0.1142 * temp + 30.308;
          } else {
            dis_mm = 0;
          }
          //Serial.print("case 4 ");    //for debugging
        } break;
      }

  return dis_mm;

}
