#include "Motor.h"
#include "FSM.h"
#include "LED.h"
#include <Servo.h>

void setup() {
  ledSETUP();
  Serial1.begin(115200);  //Open serial comms to bluetooth module
}

void loop() {
   static STATE machine_state = INITIALISING;
  //Finite-state machine Code
  switch (machine_state) {
    case INITIALISING:
      machine_state = initialising();
      break;
    case RUNNING:
      machine_state =  running();
      break;
    case FIRE:
      machine_state = fire();
      break;
    case STOPPED:
      machine_state =  stopped();
      break;
  };
}
