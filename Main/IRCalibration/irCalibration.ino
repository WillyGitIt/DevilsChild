#include "IR_Sensor.h"

  IR_Sensor s1(Short_2D120XF1Y,8);
  IR_Sensor s2(Short_2D120XF1Z,9);
  IR_Sensor s3(Medium_2Y0A21F06,10);
  IR_Sensor s4(Medium_2Y0A21F44,11);
  
void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(s1.distance());
  //Serial.println(s2.distance());
  //Serial.println(s3.distance());
   Serial.println(s4.distance());
 Serial.println("=====================================");
  delay(500);
}
