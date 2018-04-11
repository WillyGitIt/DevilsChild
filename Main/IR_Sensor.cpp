/* To control the Rover, copy and paste the code below into the Arduino
 software. Ensure the motors are connected to the correct pins. The
 code does not factor in encoders at this time*/

#include "IR_Sensor.h"
#include "main.h"
#include "Arduino.h"

void setup(SHARP type, int pin)
{
  SensorType = type;
  Sensorpin = pin;
}

float distance()
{
  float dis_mm;  //distance in mm
  
  if (SensorType == SHARP 0) //Medium_2Y0A21F21 
  {
    dis_mm = (2697 * pow(analogRead(pin),-0.787))*10; 
      if (dis_mm < 0.0)
        return 801;
      if (dis_mm >= 0.0 && temp_dis <= 10.0)
        return 99;
      if (dis_mm > 80.0)
        return 801;
    return dis_mm;
    
  }else if (SensorType == SHARP 1) //Medium_2Y0A21F44,
  {
    dis_mm = (2633.9 * pow(analogRead(pin),-0.788))*10; 
      if (dis_mm < 0.0)
        return 801;
      if (dis_mm >= 0.0 && temp_dis <= 10.0)
        return 99;
      if (dis_mm > 80.0)
        return 801;
    return dis_mm;
    
  }else if (SensorType == SHARP 2)//Short_2D120XF1Y,
  {
     dis_mm = (2050.6 * pow(analogRead(pin),-0.924))*10; 
      if (dis_mm < 0.0)
        return 301;
      if (dis_mm >= 0.0 && temp_dis <= 4.0)
        return 39;
      if (dis_mm > 30.0)
        return 301;
    return dis_mm;
    
  }else if (SensorType == SHARP 3)//Short_2D120XF1Z
  {
     dis_mm = (2559.3 * pow(analogRead(pin),-1.062))*10; 
      if (dis_mm < 0.0)
        return 301;
      if (dis_mm >= 0.0 && temp_dis <= 4.0)
        return 39;
      if (dis_mm > 30.0)
        return 301;
    return dis_mm;
  }
}

//
//STATE running() {
//  int level_bar = 0;
//  static unsigned long previous_millis;
//  static unsigned long sprevious_millis;
//  static float avg;
//  static int stotal;
//
//  int i;
//  static int avgcount;
//  if (millis() - sprevious_millis > 10) {
//    sprevious_millis = millis();
//  avgcount++;
//  if (avgcount > 30) {
//    avgcount = 0;
//    avg = stotal / 30.0;
//    stotal= 0;
//  }
//  else
//    stotal +=  read_sharp_IR_sensor(SHARP_Ya, A15);
//  }
//
//  if (millis() - previous_millis > 500) {
//    previous_millis = millis();
//
//    int raw = analogRead(A15);
//    Serial.print("s1:");
//    Serial.println(avg);
//    
//    Serial.print("raw:");
//     Serial.println(raw);
//     
//    // Serial1.print(" s2:");
//     Serial1.print(read_sharp_IR_sensor(SHARP_DX, A15));
//    // Serial1.print(" s3:");
//    // Serial1.print(read_sharp_IR_sensor(SHARP_Ya, A3));
//     //Serial1.print(" s4:");
//    // Serial1.println(read_sharp_IR_sensor(SHARP_YA, A4));
//
//
//    //2D120X 40mm - 300mm http://www.phidgets.com/products.php?product_id=3520
//    //Distance = 2076.0 / (raw - 11) + 2;
//    //
//    //2Y0A21 100mm - 800mm http://www.phidgets.com/products.php?product_id=3521
//    //Distance = 4800.0 / (raw - 20);
//    //
//    //2Y0A02 200mm - 1500mm http://www.phidgets.com/products.php?product_id=3522
//    //Distance = 9462 / (raw - 16.92);
//    //
//
//    //2Y0A21 100mm - 800mm http://www.phidgets.com/products.php?product_id=3521
//    //Distance = 4800.0 / (raw - 20);
//
//    
//    /*Serial1.print("\r[");
//    for (i = 0; i < 10; i++) {
//      if (level_bar > i)
//        Serial1.print("#");
//      else
//        Serial1.print("-");
//    }
//    //Serial.print(char(219));
//
//    Serial1.print("]");
//    Serial1.print(puntualDistance, 1);*/
//    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//    level_bar++;
//    if (level_bar > 10)
//      level_bar = 0;
//  }
//  return RUNNING;
//}
//
//
//
//int read_sharp_IR_sensor(SHARP which_one, int which_analog_pin) {
//  double temp_dis;
//  switch (which_one) {
//    case SHARP_DX:
//      //2D120X 4cm - 30cm http://www.phidgets.com/products.php?product_id=3520
//     // temp_dis = 2076.0 / (analogRead(which_analog_pin) - 11) + 2;
//     temp_dis = 2050.6 * pow(analogRead(which_analog_pin),-0.924); 
//      if (temp_dis < 0.0)
//        return 30.1;
//      if (temp_dis >= 0.0 && temp_dis <= 4.0)
//        return 3.9;
//      if (temp_dis > 30.0)
//        return 30.1;
//      return temp_dis;
//      break;
//    case SHARP_Ya:
//      //2Y0A21 10cm - 80cm http://www.phidgets.com/products.php?product_id=3521
//      temp_dis =  4800.0 / (analogRead(which_analog_pin) - 20);
//      if (temp_dis < 0.0)
//        return 80.1;
//      if (temp_dis >= 0.0 && temp_dis <= 10.0)
//        return 9.9;
//      if (temp_dis > 80.0)
//        return 80.1;
//      return temp_dis;
//      break;
//    case SHARP_YA:
//      //2Y0A02 20cm - 150cm http://www.phidgets.com/products.php?product_id=3522
//      temp_dis =  9462.0 / (analogRead(which_analog_pin) - 16.92);
//      if (temp_dis < 0.0)
//        return 150.1;
//      if (temp_dis >= 0.0 && temp_dis <= 20.0)
//        return 19.9;
//      if (temp_dis > 150.0)
//        return 150.1;
//      return temp_dis;
//      break;
//  }
//}
//
//

