#include "IR_Sensor.h"

  IR_Sensor front_left(Short_2D120XF1Y,8);
  IR_Sensor front_right(Short_2D120XF1Z,9);
  IR_Sensor side_front(Medium_2Y0A21F06,10);
  IR_Sensor side_back(Medium_2Y0A21F44,11);
  
void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
}

void loop() {
  Serial.println(front_left.distance());
  Serial.println(front_right.distance());
  Serial.println(side_front.distance());
  Serial.println(side_back.distance());
  //Serial.println("-------------------");
  delay(500);
}
