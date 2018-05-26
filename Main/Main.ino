#include "Motor.h"
#include "FSM.h"
#include "LED.h"
#include <Servo.h>
static STATE machine_state = INITIALISING;

void setup() {
  Serial.begin(9600);     //Oprn serial comms to USB 
  Serial1.begin(115200);  //Open serial comms to bluetooth module
}

void loop() {
  //Finite-state machine Code
  switch (machine_state) {
    case INITIALISING:
      machine_state = initialising();
      break;
    case SPIRALING:
      machine_state =  spiraling();
      break;
    case AVOIDANCE:
      machine_state = avoidance();
      break;
    case STOPPED:
      machine_state =  stopped();
      break;
  };
}
