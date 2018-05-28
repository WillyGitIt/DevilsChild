/*  distance() returns a distance measurement in centimetres. 
    For the short range, 
*/

#include "IR_Sensor.h"
#include "Arduino.h"


IR_Sensor::IR_Sensor(SHARP type, unsigned int pin){
    SensorType = type;     
    Sensorpin = pin;
}

float temp;
float dis_mm;  //distance in mm
float IR_Sensor::distance()
{
  for (unsigned int i = 0; i < 50; i++){
    temp += analogRead(Sensorpin);
    delay(1);
  }
 
  temp = temp * 0.02;
  
  float dis_mm;  //distance in mm
    switch(SensorType){
        case Short_2D120XF1Y: { //front left
          //dis_mm = temp;
          if (temp < 54) {
            dis_mm = 30;      
          }else if (temp < 142) {
            dis_mm = -25.55 * log(temp) + 130;
          } else {
            dis_mm = 0;
           }
        } break;    
          
        case Short_2D120XF1Z: { //front right
          //dis_mm = temp;
           if (temp < 42) {
            dis_mm = 30;      
          }else if (temp < 142 ) {
            dis_mm =  -23.7 * log(temp) + 117.89;        
           } else {
            dis_mm = 0;
           }
        } break;
          
        case Medium_2Y0A21F06:  {   //side front
          //dis_mm = temp;
          if (temp < 50) {
            dis_mm = 60;      
          }else if (temp < 224)  {
            dis_mm = 108.25*exp(-0.014*temp);
          } else {
            dis_mm = 0;
          }      
        } break;
          
        case Medium_2Y0A21F44: {    //side back
          //dis_mm = temp;
          if (temp < 50) {
            dis_mm = 60;      
          }else if (temp < 224)  {
            dis_mm = 107.42*exp(-0.015*temp);
          } else {
            dis_mm = 0;
          } 
        } break;
      }
  Serial.print("IR: ");
  Serial.println(dis_mm);
  return dis_mm;

}
