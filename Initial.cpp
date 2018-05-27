#include "Motor.h"
#include "Initial.h"
#include <Arduino.h>
#include "IR_Sensor.h"

void homing() //find a wall to go to it, then align with the wall
{
  IR_Sensor IRB(IR_Type_SF, IR_side_front_PIN);
  IR_Sensor IRF(IR_Type_SB, IR_side_back_PIN);
  motor.WallAlign();
  delay(500);
  while ((IRB.distance() + IRF.distance()) * 0.5 > Wall_Distance){
    motor.shift_left();
  }
  motor.stop();
  motor.WallAlign();
  return;
}
