
#include "Arduino.h"
#include "Logic.h"
#include "IR_Sensor.h"
#include "Motor.h"
#include "phototrans.h"
#include "Ultrasonic_Sensor.h"
#include <hcsr04.h>

void setup() {
  motor.SETUP();
  motor.enable_motors();
  Serial.begin(9600);
 // Phototrans.setup(14, 5, 15, 4, 0.2);
  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH); 
}

void loop() {
 spiral();
}
  /*//testing obstacle avoidance
  motor.forward();
  if (obstacleDetect() == true)
  {
    obstacleAvoid();
  }*/
   

  //test turn
  //motor.cw(90);
  //delay(100);

