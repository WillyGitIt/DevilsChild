
#include "Arduino.h"
#include "Logic.h"
#include "IR_Sensor.h"
#include "Motor.h"

void setup() {
  motor.SETUP();
  motor.enable_motors();
  Serial.begin(9600);
}

void loop() {
  motor.forward();
  if (obstacleDetect()){
    obstacleAvoid();
  }

}
